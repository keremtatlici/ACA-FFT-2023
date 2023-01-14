import numpy as np
import cv2

#this code is used to convert rgb image to gray image and save it as txt file

image512 = cv2.imread('datasets/rgb/512x512_rgb.jpg')
image1024 = cv2.imread('datasets/rgb/1024x1024_rgb.jpg')
image2048 = cv2.imread('datasets/rgb/2048x2048_rgb.jpg')
image4096= cv2.imread('datasets/rgb/4096x4096_rgb.jpg')
image8192 = cv2.imread('datasets/rgb/8192x8192_rgb.jpg')

gray_image512 = cv2.cvtColor(image512, cv2.COLOR_BGR2GRAY)
gray_image1024 = cv2.cvtColor(image1024, cv2.COLOR_BGR2GRAY)
gray_image2048 = cv2.cvtColor(image2048, cv2.COLOR_BGR2GRAY)
gray_image4096 = cv2.cvtColor(image4096, cv2.COLOR_BGR2GRAY)
gray_image8192 = cv2.cvtColor(image8192, cv2.COLOR_BGR2GRAY)



np.savetxt('datasets/gray/512x512_gray.txt', gray_image512, fmt='%d')
np.savetxt('datasets/gray/1024x1024_gray.txt', gray_image1024, fmt='%d')
np.savetxt('datasets/gray/2048x2048_gray.txt', gray_image2048, fmt='%d')
np.savetxt('datasets/gray/4096x4096_gray.txt', gray_image4096, fmt='%d')
np.savetxt('datasets/gray/8192x8192_gray.txt', gray_image8192, fmt='%d')


