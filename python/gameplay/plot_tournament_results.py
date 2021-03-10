import matplotlib.pyplot as plt
import numpy as np

from tournament_stats import load_stats

if __name__ == "__main__":
    entries = load_stats()["entries"]
    ne = len(entries)

    bk_wins, wt_wins, draw = (
        np.zeros(ne, dtype=np.int32),
        np.zeros(ne, dtype=np.int32),
        np.zeros(ne, dtype=np.int32),
    )
    for i, entry in enumerate(entries):
        if entry["winner"] == "bk":
            bk_wins[i] = 1
        elif entry["winner"] == "wt":
            wt_wins[i] = 1
        else:
            assert entry["winner"] == "draw"
            draw[i] = 1

    bk_sum = np.cumsum(bk_wins)
    wt_sum = np.cumsum(wt_wins)
    draw_sum = np.cumsum(draw)
    z = np.linspace(1, ne, ne)  # normalizer
    labels = ("black (Android app)", "white (shashki-ai)", "draw")

    plt.rcParams.update({"font.size": 14})

    plt.figure(figsize=(11, 7))
    plt.plot(bk_sum, "k.-")
    plt.plot(wt_sum, "b.-")
    plt.plot(draw_sum, "g.-")
    plt.legend(labels)
    plt.grid(True)
    plt.xlabel("games")
    plt.ylabel("# wins")
    plt.tight_layout()

    plt.figure(figsize=(11, 7))
    plt.plot(100.0 * bk_sum / z, "k.-")
    plt.plot(100.0 * wt_sum / z, "b.-")
    plt.plot(100.0 * draw_sum / z, "g.-")
    plt.xlabel("games")
    plt.ylabel("wins [%]")
    plt.legend(labels)
    plt.grid(True)
    plt.tight_layout()

    plt.figure(figsize=(9, 7))
    fracs = (bk_sum[-1] / ne, wt_sum[-1] / ne, draw_sum[-1] / ne)
    explode = (0.01, 0.01, 0.01)

    def slice_label(pct):
        abs_ = pct / 100.0 * ne
        return f"{pct:.1f}%\n({abs_:.0f} games)"

    patches, _, autotexts = plt.pie(
        fracs,
        # explode=explode,
        labels=labels,
        autopct=slice_label,
        startangle=90,
        colors=("k", "w", "w"),
        wedgeprops={"linewidth": 1, "edgecolor": "lightgray"},
    )
    autotexts[0].set_color("w")
    patches[2].set_hatch("//")
    plt.title(f"Distribution of wins ({ne} games)")
    plt.tight_layout()
    plt.gca().axis("equal")

    plt.show()
