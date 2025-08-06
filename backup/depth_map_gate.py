import cv2 as cv
import numpy as np
from pathlib import Path
from rosbags.highlevel import AnyReader
from cv_bridge import CvBridge
from PIL import Image


color_image = cv.imread('/home/chippu/github/ComputerVision/color_img.png')
grey_img = cv.cvtColor(color_image,cv.COLOR_BGR2GRAY)
# cv.imshow('grey scale image',grey_img)
# cv.imshow('original color image', color_image)
color_img_arr = np.array(color_image)
import cv2
import os

# Define paths
# /home/chippu/github/ComputerVision
image_dir = '/home/chippu/github/ComputerVision/train/images'
label_dir = '/home/chippu/github/ComputerVision/train/labels'
class_names = ['gate']  

def draw_annotations(image_path, label_path):
    img = cv2.imread(image_path)
    h, w = img.shape[:2]
    
    if not os.path.exists(label_path):
        return img

    with open(label_path, 'r') as f:
        for line in f:
            parts = line.strip().split()
            cls_id = int(parts[0])
            x_center, y_center, width, height = map(float, parts[1:])
            x1 = int((x_center - (width / 2)) * w) 
            y1 = int((y_center - (height / 2)) * h)
            x2 = int((x_center + (width / 2)) * w)
            y2 = int((y_center + (height / 2)) * h)
            color = (255, 0, 0)
            cv2.rectangle(img, (x1, y1), (x2, y2), color, 2)
            label = class_names[cls_id] if cls_id < len(class_names) else str(cls_id)
            cv2.putText(img, label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 2)
    
    return img,[x1,x2,y1,y2]

def contours(orig_image,box):
    for x in range(box[0],box[1]):
        for y in range(box[2],box[3]):
            pixel_color = orig_image[y,x]
            if (pixel_color[0]>= 80 and pixel_color[0]<= 140 and pixel_color[1]>= 90 and pixel_color[1]<= 150 and pixel_color[2]>= 50 and pixel_color[2]<= 130 ):
                orig_image[y,x] = [0,255, 0]
             #red [50,130], green [90,150], blue[80,140]
        


image_files = [f for f in os.listdir(image_dir) if f.endswith(('.jpg', '.png'))]

for img_file in image_files[:20]:  
    img_path = os.path.join(image_dir, img_file)
    print(img_path)
    label_path = os.path.join(label_dir, img_file.rsplit('.', 1)[0] + '.txt')
    orig_image = cv.imread(img_path)
    print(orig_image.shape)    
    annotated,box = draw_annotations(img_path, label_path)
    box_img = orig_image[box[2]:box[3],box[0]:box[1]]
    # grey_img = cv.cvtColor(orig_image,cv.COLOR_RGB2GRAY)
    # blurred = cv2.GaussianBlur(grey_img, (5, 5), 0)
    # ret, thresh = cv2.threshold(blurred, 127, 255, cv2.THRESH_BINARY)
    # contours, hierarchy = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    # # Draw all contours
    # contoured_image = orig_image.copy()
    # cv.drawContours(contoured_image, contours, -1, (0, 255, 0), 2)
    # cv.imshow('grey image',orig_image)
    # cv2.imshow("Contours", contoured_image)
    contours(orig_image,box)
    cv.imshow('image',orig_image)
    cv2.imshow('Annotated Image', annotated)
    cv2.waitKey(2000)  

cv2.destroyAllWindows()

cv.waitKey(10000)
cv.destroyAllWindows()




# print(depth_array[110,100]/1000)

# <x_center>: The x-coordinate of the center of the bounding box, normalized by the width of the image (a float between 0 and 1).
# <y_center>: The y-coordinate of the center of the bounding box, normalized by the height of the image (a float between 0 and 1).
# depth_array = depth_array / np.max(depth_array)
# print(depth_array[101,315])
# x,y = 10,212
# depth_val = depth_map[x,y]
# normalized_image = cv.normalize(depth_map, None, alpha=0, beta=255, norm_type=cv.NORM_MINMAX)
# cv.imshow('normalized image',normalized_image)
# print(f"the depth value at x and y is: {bit_depth}")

# frombytes
# depth_map = cv.imread('/home/chippu/github/ComputerVision/depth_map_img.png')
# depth_map = Image.frombytes(mode_depth, (depth_map_rosmsg.width, depth_map_rosmsg.height), depth_map_rosmsg.data)
# <object-class> <x_center> <y_center> <width> <height> 
# 
# cv.imshow('original depth image',depth_map)
# depth_array = np.array(depth_map, dtype=np.float32)
