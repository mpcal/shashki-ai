import skimage
from skimage import color, io


def load_image(path, blur=None):
    im = skimage.img_as_float(io.imread(path))
    im = color.rgb2gray(color.rgba2rgb(im))
    if blur:
        im = filters.gaussian(im, sigma=(blur, blur))
    return im
