from pathlib import Path
from rosbags.highlevel import AnyReader
from cv_bridge import CvBridge
import cv2
from PIL import Image
from ultralytics import YOLO
import numpy as np
import random
from sklearn.cluster import KMeans

def show_hsv_val(event, x,y,flags, param):
    if event == cv2.EVENT_MOUSEMOVE:
        hsv = hsv_image[y,x]
        print(f"hsv at {x} and {y}: {hsv}")

cv2. namedWindow('hsv image')
cv2.setMouseCallback('hsv image',show_hsv_val)
counter = 1
def contours(box_image,box):
    bridge_pixels = []
    for y in range(box[2],box[3]):
        for x in range(box[0],box[1]):
            pixel_color = box_image[y][x]
            if (pixel_color[0]>= 80 and pixel_color[0]<= 140 and pixel_color[1]>= 90 and pixel_color[1]<= 150 and pixel_color[2]>= 50 and pixel_color[2]<= 130 ):
                #  box_image[y,x] = [0,255, 0]
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
    # print(pixel_depth)
    if len(pixel_depth) != 0:
        average =  sum(pixel_depth)/ len(pixel_depth)
        return average
    else:
        return 0

# def find_corners(box_image,box,bridge_pixels,cv_depth):

def combine_masks(mask_list):
    mask_combined = cv2.bitwise_or(mask_list[0], mask_list[1])
    for i in range(2,len(mask_list)):
        mask_combined = cv2.bitwise_or(mask_combined, mask_list[i])
    return mask_combined
    
file = "/home/chippu/github/ComputerVision/gate_pipe_model.pt"
model = YOLO(file)

with AnyReader([Path("/home/chippu/github/ComputerVision/may_4_gate_rosbag")]) as reader:

    rgb_connections = [x for x in reader.connections if x.topic == '/zed/zed_node/left/image_rect_color']
    depth_connections = [x for x in reader.connections if x.topic == '/zed/zed_node/depth/depth_registered']
    rgb_msgs = {}
    depth_msgs = {}
    count = 1
    for connection, timestamp, rawdata in reader.messages(connections = rgb_connections + depth_connections):
        if count < 1:  #5300
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
            grey_scale = cv2.cvtColor(cv_bgr, cv2.COLOR_BGR2GRAY)
            results = model(cv_bgr)
            detections = results[0]
            # boxes = detections.boxes
            
            boxed_img = results[0].plot()
            box = find_box(boxed_img, detections)
            

            if box != 0:
                bridge_pixels = contours(boxed_img,box) #code to find individual pixels 
                
                cropped_image = cv_bgr[box[2]:box[3],box[0]:box[1]]
                hsv_image = cv2.cvtColor(cropped_image, cv2.COLOR_BGR2HSV)
                lower_red1 = np.array([60,80, 60])
                upper_red1 = np.array([93,255, 255])
               
                lower_red3 = np.array([50,60, 100])
                upper_red3 = np.array([93,100, 160])

                lower_red2 = np.array([85,100,100])
                upper_red2 = np.array([105,175,190])

                lower_red4 = np.array([40,40,80])
                upper_red4 = np.array([100,120,255])

                # lower_white = np.array([90,90,185])
                # upper_white = np.array([100,225,230])
                lower_red5 = np.array([0,0,180])
                upper_red5 = np.array([80,140,256])


                mask1 = cv2.inRange(hsv_image, lower_red1, upper_red1)
                mask2 = cv2.inRange(hsv_image, lower_red5, upper_red5)
                mask3 = cv2.inRange(hsv_image, lower_red2, upper_red2)
                mask4 = cv2.inRange(hsv_image, lower_red3, upper_red3)
                mask5 = cv2.inRange(hsv_image, lower_red4, upper_red4)
                
                mask_combined = combine_masks([mask3, mask5,mask2,mask4,mask1]) # 
                # cv2.imshow("hsv",mask_combined)
                mask_hsv = cv2.bitwise_and(hsv_image,hsv_image,mask = mask_combined) 
                # print(mask_hsv.shape)
                cv2.imshow("hsv image",hsv_image)
                cv2.imshow("masked image",mask_hsv)
                if (cv2.countNonZero(mask_combined) == 0):
                    print("empty")
                
                # Find contours of the red areas
                kernel = np.ones((2,2),np.uint8)
                kernel_opening = np.ones((2,2),np.uint8)
                opening = cv2.morphologyEx(mask_hsv, cv2.MORPH_OPEN, kernel_opening)
                cv2.imshow("opened image",opening)
                kernel_closing_small = np.ones((4,3),np.uint8)
                kernel_closing_large = np.ones((20,10),np.uint8)
                # opening = cv2.morphologyEx(mask_hsv, cv2.MORPH_OPEN, kernel)     
                closing_small = cv2.morphologyEx(opening, cv2.MORPH_CLOSE, kernel_closing_small)
                # cv2.imshow("closing small", closing_small)
                closing_large = cv2.morphologyEx(closing_small, cv2.MORPH_CLOSE, kernel_closing_large)
                cv2.imshow("morphed",closing_large)
                print("length :",len(closing_large.shape))
                masked_image_gray = cv2.cvtColor(closing_large, cv2.COLOR_BGR2GRAY)
                _, thresholded_mask = cv2.threshold(masked_image_gray, 1, 255, cv2.THRESH_BINARY)
                contour, hierarchy = cv2.findContours(thresholded_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
                #changing code from here
                dst = np.zeros((cv_bgr.shape[0], cv_bgr.shape[1], 3), dtype=np.uint8)
                mask = np.zeros((cv_bgr.shape[0], cv_bgr.shape[1]), dtype=np.uint8)
                poly = []
                
                big_contour = max(contour, key = cv2.contourArea)
                area = cv2.contourArea(big_contour)

                # for cnt in big_contour:
                epsilon = 0.03*cv2.arcLength(big_contour,True)
                approx = cv2.approxPolyDP(big_contour, epsilon, True)
                poly.append(approx)

                # print(poly)
                x_offset = box[0]
                y_offset = box[2]
                for i in range(len(poly)):
                    points = poly[i].reshape(len(poly[i]), 2).tolist()
                    color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
                    cv2.drawContours(dst, poly, i, color, 1, cv2.LINE_8, hierarchy, 0)
                    for point in points:
                        # print(point)
                        full_point = (point[0] + x_offset, point[1] + y_offset)
                        cv2.circle(cv_bgr, full_point, radius=5, color=(0, 0, 255), thickness=-1)


                cv2.imshow('canvasOutput', dst)
                cv2.drawContours(cropped_image, contour, -1, (0, 255, 0), 2)
                #code change implemented till here 
                cv2.imshow('orginal image',cv_bgr)


                cv2.imshow('canvasOutput', dst)
                cv2.drawContours(cropped_image, contour, -1, (0, 255, 0), 2)
                # #code change implemented till here

                cv2.imshow("mask",mask_hsv)
                cv2.imshow("cv bgr",cv_bgr)

            
            cv_depth = bridge.imgmsg_to_cv2(depth_msgs[time_key])
            print(cv_depth)
            avg_depth = find_avg_gate_depth(bridge_pixels,cv_depth)
            print("the average depth is:",avg_depth)
          
            depth_map = Image.frombytes('F', (msg.width, msg.height), msg.data)
            depth_save = depth_map.tobytes()
            key = cv2.waitKey(10)
           

cv2.destroyAllWindows()


