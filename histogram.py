import numpy as np
import cv2
import matplotlib.pyplot as plt

image = cv2.imread("one.jpg")
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

histogram, bin_edges = np.histogram(gray, bins=256, range=(0, 255))


plt.figure()
plt.title("Grayscale Histogram")
plt.xlabel("grayscale value")
plt.ylabel("pixel count")
plt.xlim([0.0, 255])  
plt.plot(bin_edges[0:-1], histogram) 
plt.show()


equ = cv2.equalizeHist(gray)
cv2.imwrite('img4.jpg', equ)

histogram, bin_edges = np.histogram(equ, bins=256, range=(0, 255))


plt.figure()
plt.title("Grayscale Histogram")
plt.xlabel("grayscale value")
plt.ylabel("pixel count")
plt.xlim([0.0, 255])  
plt.plot(bin_edges[0:-1], histogram) 
plt.show()
