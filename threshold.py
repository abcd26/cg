import cv2
import numpy


image = cv2.imread("image.jpg")
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

for i in range(len(gray)):
    for j in range(len(gray[i])):
        if gray[i][j]>160:
            gray[i][j] = 0
        else:
            gray[i][j] = 255
            
img = numpy.array(gray)

cv2.imwrite('img1.jpg', img)