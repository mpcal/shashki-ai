import json
import numpy as np
from skimage import feature, io, transform

from templates import load_template
from shared import load_image


class BoardScreen:
    """Screenshots are assumed to come from the Russian Checkers app on Android"""

    def __init__(self, im):
        """
        Args: im: screenshot, typically from initial position, could be any screen

        Initializes fields x1, y1, x2, y2 which define the board rectangle, (x1, y1) is
        the top left corner, (x2, y2) the bottom right corner
        """
        rect = BoardScreen.get_rect(im)
        self.x1, self.y1, self.x2, self.y2 = rect
        self.width = self.x2 - self.x1
        self.height = self.y2 - self.y1

        self._cell_width = (rect[2] - rect[0]) / 8.0
        self._cell_height = (rect[3] - rect[1]) / 8.0

        # Note: be sure to pass self.width and self.height rather than the image width
        # and height! This is because the reference lengths in the json file are
        # referring to the square size and not the image size
        do_load = lambda f: load_template(self.width, self.height, "board", f)
        self.t_bk_man = do_load("templates/black_man.png")
        self.t_wt_man = do_load("templates/white_man.png")
        self.t_bk_king = do_load("templates/black_king.png")
        self.t_wt_king = do_load("templates/white_king.png")
        self.t_empty = do_load("templates/empty.png")

        self._im = im

    def read_state(self):
        """Reads the board state"""

        def best_match(square):
            nonlocal ix  # debug
            scores = np.asarray(
                [
                    np.max(feature.match_template(square, self.t_bk_man)),
                    np.max(feature.match_template(square, self.t_wt_man)),
                    np.max(feature.match_template(square, self.t_bk_king)),
                    np.max(feature.match_template(square, self.t_wt_king)),
                    np.max(feature.match_template(square, self.t_empty)),
                ]
            )

            return np.argmax(scores)

        w, h = self._cell_width, self._cell_height
        bk = wt = 0
        for ix in range(32):
            xc, yc = self.ix_to_x_y(ix)
            square = self._im[
                round(yc - h / 2) : round(yc + h / 2),
                round(xc - w / 2) : round(xc + w / 2),
            ]

            m = best_match(square)
            if m == 0:
                bk |= 1 << ix
            elif m == 1:
                wt |= 1 << ix
            elif m == 2:
                bk |= 1 << (ix + 32)
            elif m == 3:
                wt |= 1 << (ix + 32)

        return bk, wt

    def ix_to_x_y(self, ix: int):
        row = ix // 4
        col = (2 * ix) % 8 + int(row % 2 == 0)

        x = self.x1 + int((0.5 + col) * self._cell_width)
        y = self.y1 + int((0.5 + row) * self._cell_height)

        return x, y

    def x_y_to_ix(self, x: float, y: float):
        col = round((x - self.x1) / self._cell_width - 0.5)
        row = round((y - self.y1) / self._cell_height - 0.5)
        return row * 4 + col // 2

    @staticmethod
    def get_rect(im):
        """
        Find inner board rectangle from a grayscale image of a screenshot
        """
        corner = load_image("templates/corner_ne.png")
        result = feature.match_template(im, corner)
        ixs = np.argsort(result, axis=None)[-48:]
        ys, xs = np.unravel_index(ixs, result.shape)
        xs = xs + corner.shape[1] // 2 - (corner.shape[1] % 2 == 0) * 0.5
        ys = ys + corner.shape[0] // 2 - (corner.shape[1] % 2 == 0) * 0.5

        # for x, y in zip(xs, ys):
        #     ax.add_patch(plt.Circle((x, y), 7, color="b", alpha=0.5))

        def get_borders(zs):
            zs = np.sort(zs)
            ends = np.where(np.diff(zs) > 20)[0]  # end indices of y-clusters
            z1 = np.mean(zs[: ends[0] + 1])
            z2 = np.mean(zs[ends[-1] + 1 :])
            cell_width = (z2 - z1) / 6
            return z1 - cell_width, z2 + cell_width

        x1, x2 = get_borders(xs)
        y1, y2 = get_borders(ys)

        return x1, y1, x2, y2

    def get_screen(self):
        return self._im

    def __str__(self):
        return (
            f"BoardRect(x1={self.x1:.5f}, "
            f"y1={self.y1:.5f}, x2={self.x2:.5f}, y1={self.y2:.5f})"
        )

