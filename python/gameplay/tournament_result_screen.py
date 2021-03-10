import matplotlib.pyplot as plt
import numpy as np
from skimage import feature

from shared import load_image
from templates import load_template


class GameResult:
    BLACK_WINS = 0
    WHITE_WINS = 1
    DRAW = 2


def detect_tournament_result(im):
    """
    Determine type of screen from a grayscale screenshot

    Screenshots are assumed to come from the Russian Checkers app on Android

    Returns a (`GameResult`, next_xy) tuple on success and (None, None) if detection
    failed. next_xy is the screen location to tap to close the screen and continue with
    a fresh game
    """
    do_load = lambda f: load_template(im.shape[1], im.shape[0], "screens", f)
    _t_blacks_wins = do_load("templates/black_wins_screen.png")
    _t_white_wins = do_load("templates/white_wins_screen.png")
    _t_draw = do_load("templates/draw_screen.png")
    _t_button = do_load("templates/new_game_button.png")

    # compute matches across entire screen, corr are normalized to [-1, 1]
    corr = np.asarray(
        [
            np.max(feature.match_template(im, _t_blacks_wins)),
            np.max(feature.match_template(im, _t_white_wins)),
            np.max(feature.match_template(im, _t_draw)),
        ]
    )
    print(f"Result screen corr: bk={corr[0]:.6f} wt={corr[1]:.6f} draw={corr[2]:.6f}")

    # ascending sort, element at ix[-1] has highest correlation
    ix = np.argsort(corr)

    # require minimum correlation
    if corr[ix[-1]] < 0.9 or abs(corr[ix[-1]] / (corr[ix[-2]] + 1e-9)) < 1.05:
        plt.imsave("out/_RESULT_CORR_FAILURE_SCREEN.png", im, cmap='gray')
        return None, None

    # find "new game" button
    corr = feature.match_template(im, _t_button, pad_input=True)
    cy, cx = np.unravel_index(np.argmax(corr), im.shape)
    print(f"Button corr: {np.max(corr):.6f}")
    if np.max(corr) < 0.9:
        plt.imsave("out/_BUTTON_CORR_FAILURE_SCREEN.png", im, cmap='gray')
        return None, None

    if ix[-1] == 0:
        return GameResult.BLACK_WINS, (cx, cy)
    elif ix[-1] == 1:
        return GameResult.WHITE_WINS, (cx, cy)
    elif ix[-1] == 2:
        return GameResult.DRAW, (cx, cy)
    else:
        raise NotImplementedError("Unknown GameResult")
