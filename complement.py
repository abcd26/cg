import cv2

image = cv2.imread(r"one.jpg")

row = len(image)
col = len(image[0])
gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)

for i in range(row):
    for j in range(col):
        gray[i][j] = 255-gray[i][j]
        
cv2.imwrite("img5.jpg",gray)