import cv2
import numpy as np
from skimage.util import random_noise
from math import log10, sqrt

def psnr(original, noise_removed):
    mse = np.mean((original - noise_removed) ** 2)
    if mse==0:
        return 100
    max_pixel = 255.0
    psnr = 20 * log10(max_pixel/sqrt(mse))
    return psnr

image = cv2.imread("one.jpg")
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

noise_img = random_noise(gray, mode='s&p', amount=0.3)

noise_img = np.array(255*noise_img)

cv2.imwrite('img2.jpg', noise_img)

image = cv2.imread("img2.jpg")
gray1 = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
cv2.fastNlMeansDenoising(gray1, gray1, 30.0, 7, 100);

cv2.imwrite('img3.jpg', gray1)

img = cv2.imread("one.jpg")
orig = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
print("PSNR VALUES OF IMAGES:", psnr(orig, gray1))