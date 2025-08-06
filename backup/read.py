import cv2 as cv

#reading images
# img = cv.imread('ComputerVision/photo1.jpeg')
# cv.imshow('AmmaBapa',img)
#cv.waitKey(0)

#reading videos
cam = cv.VideoCapture(0)
# Check if the camera is opened successfully
if not cam.isOpened():
    print("Error: Could not open webcam.")
    exit()
while True:
    ret, frame = cam.read()
    cv.imshow('camera',frame)
    if cv.waitKey(1) == ord('q'):  #quits when you press q
        break

cam.release()
cv.destroyAllWindows()