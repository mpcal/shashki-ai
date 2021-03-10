import json
import numpy as np
from skimage import feature, io, transform

from shared import load_image

META_FILE = "templates/meta.json"


def load_template(screen_w, screen_h, templ_type, fname):
    """
    Loads and scales a template for matching using convolution with a screen

    templ_type: "board", "screen", ... (top level key in META_FILE)
    """
    with open(META_FILE, "r") as hf:
        meta = json.load(hf)
        meta = meta[templ_type]

    scale = (
        screen_h / meta["ref-height"],
        screen_w / meta["ref-width"],
    )

    # load image and scale
    im = load_image(fname)
    im = transform.rescale(im, scale=scale)

    return im

