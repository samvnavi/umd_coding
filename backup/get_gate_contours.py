import cv2
import numpy as np

img = cv2.imread("/home/chippu/github/ComputerVision/translation_perpendicular/gate_left_120_40.jpg")

cv2.imshow("actual image",img)

cv2.waitKey(0)