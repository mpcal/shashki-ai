import datetime as dt
import os
import subprocess
import sys
import time

import cv2
import matplotlib.pyplot as plt
import numpy as np
import requests

import adb_wrapper
import tournament_stats
from board_screen import BoardScreen
from shared import load_image
from tournament_result_screen import GameResult, detect_tournament_result

# Game tree search depth. First value is search depth if there's only men on the board,
# second value is the search depth if at least one king is present. For larger values of
# the first parameter you man want to deduct 1 or 2 for the second value. The choice
# here depend on your time budget, for me (12, 11) was striking a good balance. Remember
# that the computation time will scale ~ exp(depth)
SEARCH_DEPTH = (12, 11)

# If True, the final board of every game (i.e. the board before white's last move) will
# be saved. This will give you an impression of how tight each game was won or lost
SAVE_BOARDS = False

PNG = "cache/screen.png"


def _show_image(img, show=True):
    plt.figure(figsize=(7, 12))
    vmax = 255 if np.max(img) > 1 else 1
    plt.imshow(img, cmap="gray", vmin=0, vmax=vmax)
    plt.tight_layout()

    if show:
        plt.show()


def _save_image(fname, im):
    vmax = 255 if np.max(im) > 1 else 1
    plt.imsave(fname, im, cmap="gray", vmin=0, vmax=vmax)


def _adb_connection_check():
    devices = adb_wrapper.check_connections()
    if len(devices) != 1:
        print(f"None or too many Android devices on ADB link: {devices}")
        sys.exit(1)
    print("Connected Android device:", devices[0])


def _best_move(bk, wt, blacks_turn, cap_from=None):
    """
    cap_from: capturing from location
    """
    player = "bk" if blacks_turn else "wt"
    is_king_present = bk > 0xffffffff or wt > 0xffffffff
    strat = f"negamax-ab,{SEARCH_DEPTH[1 if is_king_present else 0]}"
    cap_from = "" if cap_from is None else f"&capfrom={cap_from}"
    query = (
        f"http://localhost:9080/v1/moves/best/?bk={bk}&wt={wt}"
        f"&player={player}&strat={strat}{cap_from}"
    )
    resp = requests.get(query)

    moves = []
    if resp.status_code != 200:
        print(f"REST endpoint: HTTP {resp.status_code}: {resp.reason}")
        print(f"> reason:", resp.text)
    else:
        resp = resp.json()
        for mv in resp["moves"]:
            from_ = mv & 0b0000000000011111
            to = (mv & 0b0001111100000000) >> 8
            moves.append((from_, to))

    return moves


def _get_screen(retries=10):
    print("> reading screen from device...")
    for i in range(retries):
        try:
            adb_wrapper.capture_screen(PNG)
            time.sleep(0.1)
            im = load_image(PNG)
        except:
            continue
        return im

    raise RuntimeError(f"Screen capture FAILED, giving up after {retries} retries")


def _get_board(retries=5):
    # capture screen
    im = _get_screen(10)

    # extract the board
    for i in range(retries):
        try:
            board = BoardScreen(im)
            bk, wt = board.read_state()
        except Exception as ex:
            print(f"> board extraction failed, retrying.. {i+1}/{retries}")
            print("  reason: ", ex)
            continue
        return board, bk, wt, False

    # board extraction failed, see if it's a result screen
    res, next_xy = detect_tournament_result(im)
    if res is None:
        raise RuntimeError(
            f"Failed reading screen either as board or tournament result"
        )

    # so it's a result screen, update tournament stats and set up next game
    tournament_stats.update_stats(res)
    if res == GameResult.BLACK_WINS:
        print("\n============= Game over, BLACK wins =============\n")
    elif res == GameResult.WHITE_WINS:
        print("\n============= Game over, WHITE wins =============\n")
    elif res == GameResult.DRAW:
        print("\n============= Game over, it's a DRAW =============\n")
    else:
        raise NotImplementedError("Bad game result")
    adb_wrapper.tap(*next_xy)
    time.sleep(0.5)

    # we should have a fresh board now, capture screen and find it
    t4 = _get_board()
    return t4[0], t4[1], t4[2], True


def _play_continuously():
    def png_name(game, ply):
        return "out" + os.sep + f"g{game:05d}_p{ply:03d}.png"

    blacks_turn = False  # always false since we're playing white

    # game and ply counters
    game = 1
    ply = 1

    while True:
        now_str = dt.datetime.now().strftime("%b %d, %H:%M:%S LT")
        print(f"\nGame {game}, Ply {ply} [{now_str}]")

        # read screen, parse board (or fail completely after five retries)
        board, bk, wt, reset = _get_board(5)
        if reset:
            game += 1
            ply = 1

        # query endpoint
        print(f"> querying shaski-ai, bk={bk}, wt={wt}, blacks_turn={blacks_turn} ...")
        moves = _best_move(bk, wt, blacks_turn)
        print(f"> received {len(moves)} move(s)")

        # save board, write directly to board image
        if SAVE_BOARDS:
            im = 255 * board.get_screen()
            seq = ", ".join([f"({f} -> {t})" for f, t, in moves])
            cv2.putText(
                im,
                f"White's move seq: {seq}",
                (10, 35),
                cv2.FONT_HERSHEY_DUPLEX,
                0.8,
                (255, 255, 255, 255),
                1,
            )

            # save board, keeping only the final one of each a game
            _save_image(png_name(game, ply), im)
            prev = png_name(game, ply - 2)
            ply > 1 and os.path.exists(prev) and os.remove(prev)

        # execute move
        for i, (from_, to) in enumerate(moves):
            print(f"> executing move {from_} -> {to}")
            if i == 0:
                adb_wrapper.tap(*board.ix_to_x_y(from_))
                time.sleep(1.0)
                adb_wrapper.tap(*board.ix_to_x_y(to))
            else:
                adb_wrapper.tap(*board.ix_to_x_y(to))

            time.sleep(0.5)

        print(f"> waiting for black to make his move...")
        time.sleep(5.0)

        ply += 2


def _print_board(im: np.ndarray):
    board = BoardScreen(im)
    bk, wt = board.read_state(im)
    subprocess.run(["../../build/shashki_ai", "print", str(bk), str(wt)])


def _show_board_rect(im: np.ndarray):
    board = BoardScreen(im)

    _, ax = plt.subplots(figsize=(7, 15))
    plt.imshow(im, cmap=plt.cm.gray)

    plt.plot([0, im.shape[1]], [board.y1, board.y1], "b")
    plt.plot([0, im.shape[1]], [board.y2, board.y2], "b")
    plt.plot([board.x1, board.x1], [0, im.shape[0]], "b")
    plt.plot([board.x2, board.x2], [0, im.shape[0]], "b")

    plt.tight_layout()
    plt.show()


if __name__ == "__main__":
    # sanity checks
    # _adb_connection_check()
    # _show_board_rect(im)

    # adb_wrapper.capture_screen(PNG)
    # _print_board(im)

    _play_continuously()
