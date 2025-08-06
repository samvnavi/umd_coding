from pathlib import Path
from rosbags.highlevel import AnyReader
from cv_bridge import CvBridge
import cv2
from PIL import Image
from ultralytics import YOLO
import numpy as np
import matplotlib
matplotlib.use('TkAgg')

counter = 1
img_counter = 1
def contours(box_image,box):
    bridge_pixels = []
    for y in range(box[2],box[3]):
        for x in range(box[0],box[1]):
            pixel_color = box_image[y][x]
            if (pixel_color[0]>= 80 and pixel_color[0]<= 140 and pixel_color[1]>= 90 and pixel_color[1]<= 150 and pixel_color[2]>= 50 and pixel_color[2]<= 130 ):
                 box_image[y,x] = [0,255, 0]
                 bridge_pixels.append([y,x])
    return bridge_pixels
        

def find_box(boxed_img,detections):
    best_conf = 0
    best_box = None
    if (len(detections.boxes) == 0):
        return 0
    else:
        for box in detections.boxes: 
            confidence = box.conf.item()
            if (confidence > best_conf):
                print(f"Confidence: {confidence:.2f}")
                best_box = box
                best_conf = confidence

        x1, y1, x2, y2 = map(int, best_box.xyxy[0].tolist()) 
        cv2.rectangle(boxed_img, (x1, y1), (x2, y2), (0, 255, 0), 2)
        # Put confidence text above the box
        label = f"{confidence:.2f}"
        cv2.putText(boxed_img, label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 
                    0.6, (0, 255, 0), 2)
        return [x1,x2,y1,y2]
    
def find_avg_gate_depth(bridge_pixels,cv_depth):
    pixel_depth = []
    for y,x in bridge_pixels:
        each_depth = cv_depth[y,x]
        if (not np.isnan(each_depth)) and (not np.isinf(each_depth)):
            pixel_depth.append(each_depth)
   
    if len(pixel_depth) != 0:
        average =  sum(pixel_depth)/ len(pixel_depth)
        return average
    else:
        return 0

# def find_corners(box_image,box,bridge_pixels,cv_depth):
def find_pipes(bridge_pixels,box,boxed_img): #box = x1,x2,y1,y2
    left_bound = box[0] 
    right_bound = box[1]
    top_bound = box[2]
    left_pipe = []
    right_pipe = []
    mid_val = (right_bound + left_bound)/2
    for y,x in bridge_pixels:
        if x < mid_val:
            if ((x - left_bound) < (y - top_bound)):
                boxed_img[y,x] = [255,0,0]
                left_pipe.append((y,x))
        else:
            if ((right_bound - x) < (y - top_bound)):
                boxed_img[y,x] = [0,0,255]
                right_pipe.append((y,x))

    return left_pipe,right_pipe
    

def find_mid_point(left_pipe,right_pipe,cv_depth):
    left_pipe_depth = []
    right_pipe_depth = []
    for y,x in left_pipe:
        each_depth = cv_depth[y,x]
        if (not np.isnan(each_depth)) and (not np.isinf(each_depth)):
            left_pipe_depth.append(each_depth)
    for y,x in right_pipe:
        each_depth = cv_depth[y,x]
        if (not np.isnan(each_depth)) and (not np.isinf(each_depth)):
            right_pipe_depth.append(each_depth)
    if len(right_pipe_depth) != 0:
        right_average =  sum(right_pipe_depth)/ len(right_pipe_depth)
    else:
        right_average = 0
    if len(left_pipe_depth) != 0:
        left_average =  sum(left_pipe_depth)/ len(left_pipe_depth)
    else:
        left_average = 0
    mid_point = (left_average + right_average)/2
    return mid_point

file = "/home/chippu/github/ComputerVision/best.pt"
model = YOLO(file)

with AnyReader([Path("/home/chippu/github/ComputerVision/mar_9_zed_gate_rosbag")]) as reader:

    rgb_connections = [x for x in reader.connections if x.topic == '/zed/zed_node/left/image_rect_color']
    depth_connections = [x for x in reader.connections if x.topic == '/zed/zed_node/depth/depth_registered']
    rgb_msgs = {}
    depth_msgs = {}
    count = 1
    for connection, timestamp, rawdata in reader.messages(connections = rgb_connections + depth_connections):
        if count < 5000:
            count += 1
            print(count)
            continue

        msg = reader.deserialize(rawdata, connection.msgtype)
        sec = msg.header.stamp.sec
        nanosec = msg.header.stamp.nanosec
        time_key = (sec, nanosec)  
        if connection.topic == "/zed/zed_node/left/image_rect_color":
             rgb_msgs[time_key] = msg
        elif connection.topic == "/zed/zed_node/depth/depth_registered":
             depth_msgs[time_key] = msg

        if time_key in rgb_msgs and time_key in depth_msgs:
            bridge  = CvBridge()
            cv_bgr = bridge.imgmsg_to_cv2(rgb_msgs[time_key], "bgr8")
            results = model(cv_bgr)
            detections = results[0]
            boxes = detections.boxes
            boxed_img = results[0].plot()
            box = find_box(boxed_img, detections)
            if box != 0:
                bridge_pixels = contours(boxed_img,box)
                left_pipe, right_pipe = find_pipes(bridge_pixels,box,boxed_img)
                cv2.imshow("Detection", boxed_img)
                cropped_image = cv_bgr[box[2]:box[3],box[0]:box[1]]
                
                imgray = cv2.cvtColor(cropped_image, cv2.COLOR_BGR2GRAY)
                cv2.imshow("gate",imgray)
                ret, thresh = cv2.threshold(imgray, 127, 255, 0)
                contour, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
                
                cv2.drawContours(cropped_image, contour, -1, (0,255,0), 3)
                # cv2.drawContours(cropped_image, contours, -1, (0,255,0), 3)
                cv2.imshow("contors",cropped_image)
                cv_depth = bridge.imgmsg_to_cv2(depth_msgs[time_key])
                mid_point = find_mid_point(left_pipe,right_pipe,cv_depth)
                print(f"mid point {mid_point}")
            cv2.imshow("yote", cv_bgr)
            cv2.imshow("depth map",cv_depth)
            depth_map = Image.frombytes('F', (msg.width, msg.height), msg.data)
            depth_save = depth_map.tobytes()
            key = cv2.waitKey(10)

cv2.destroyAllWindows()

