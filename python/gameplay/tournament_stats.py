import datetime as dt
import json
import os

from tournament_result_screen import GameResult

RESULTS_FILE = "out/tournament_results.json"


def load_stats():
    if os.path.exists(RESULTS_FILE):
        with open(RESULTS_FILE, "r") as fp:
            return json.load(fp)
    return {"entries": []}


def update_stats(res: GameResult):
    """NOT THREAD SAFE--do not call from separate processes"""
    entries = load_stats()["entries"]

    # add an entry
    entry = {
        "millis": round(
            (dt.datetime.utcnow() - dt.datetime(1970, 1, 1)).total_seconds() * 1000
        )
    }
    if res == GameResult.BLACK_WINS:
        entry["winner"] = "bk"
    elif res == GameResult.WHITE_WINS:
        entry["winner"] = "wt"
    elif res == GameResult.DRAW:
        entry["winner"] = "draw"
    else:
        raise NotImplementedError("Unknown GameResult")

    entries.append(entry)

    # write them back to disk
    with open(RESULTS_FILE, "w") as fp:
        json.dump({"entries": entries}, fp, indent=2)
