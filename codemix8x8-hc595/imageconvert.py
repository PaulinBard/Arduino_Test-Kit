import cv2


image = cv2.imread("image.jpg")


bw_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)


resized_image = cv2.resize(bw_image, (8, 8), interpolation=cv2.INTER_LINEAR)

