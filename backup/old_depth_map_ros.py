from pathlib import Path
from rosbags.highlevel import AnyReader
from cv_bridge import CvBridge
import cv2
from PIL import Image
from ultralytics import YOLO
import numpy as np

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
            # boxes = detections.boxes
            
            boxed_img = results[0].plot()
            box = find_box(boxed_img, detections)
            
            if box != 0:
                bridge_pixels = contours(boxed_img,box) #code to find individual pixels 
                # cv2.imshow("Detection", boxed_img)
                gray = cv2.cvtColor(boxed_img, cv2.COLOR_BGR2GRAY)
                blurred = cv2.GaussianBlur(gray, (5, 5), 0)
                _, thresh_blurred = cv2.threshold(blurred, 127, 255, cv2.THRESH_BINARY)
                kernel = np.ones((5, 5), np.uint8)
                thresh_blurred = cv2.morphologyEx(thresh_blurred, cv2.MORPH_CLOSE, kernel)
                new_contours, _ = cv2.findContours(thresh_blurred, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
                cv2.drawContours(boxed_img, new_contours, -1, (0, 255, 0), 2)
                cv2.imshow('Contours', boxed_img)


                cropped_image = cv_bgr[box[2]:box[3],box[0]:box[1]]
                imgray = cv2.cvtColor(cropped_image, cv2.COLOR_BGR2GRAY)
                kernel = np.ones((2,2),np.uint8)
                tophat = cv2.morphologyEx(imgray, cv2.MORPH_TOPHAT, kernel)
                ret, thresh = cv2.threshold(tophat, 50, 255, cv2.THRESH_BINARY)

                contour, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
                hsv_image = cv2.cvtColor(cropped_image, cv2.COLOR_BGR2HSV)
                lower_red1 = np.array([60,80, 60])
                upper_red1 = np.array([90,255, 255])
                mask1 = cv2.inRange(hsv_image, lower_red1, upper_red1)
                # mask2 = cv2.inRange(hsv_image, lower_red2, upper_red2)
                # mask3 = cv2.inRange(hsv_image,lower_brown,upper_brown)
                # mask = cv2.bitwise_or(mask1)
                # mask =  cv2.bitwise_or(mask, mask3)
                # mask = cv2.morphologyEx(mask1, cv2.MORPH_OPEN, kernel)
                
                # print(cropped_image.shape)
                mask_hsv = cv2.bitwise_and(hsv_image,hsv_image,mask = mask1) 
                # print(mask_hsv.shape)
                if (cv2.countNonZero(mask1) == 0):
                    print("empty")
                
                # Find contours of the red areas
                kernel_closing = np.ones((20,17),np.uint8)
                red_cont, _ = cv2.findContours(mask1, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
                closing = cv2.morphologyEx(mask_hsv, cv2.MORPH_CLOSE, kernel_closing)
                opening = cv2.morphologyEx(closing, cv2.MORPH_OPEN, kernel)     
                close_complete = cv2.morphologyEx(opening, cv2.MORPH_CLOSE, kernel_closing)
                cv2.imshow("opening", opening)
                cv2.imshow("closing", close_complete)
                # ret, thresh = cv2.threshold(opening, 50, 255, cv2.THRESH_BINARY)
                # contour, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
                cv2.imshow("mask",mask_hsv)
                for c in red_cont:
                    x, y, w, h = cv2.boundingRect(c)
                    cv2.rectangle(cropped_image, (x, y), (x + w, y + h), (0, 255, 0), 3)
                # cv2.imshow("mask",mask)
                cv2.imshow("hsv image",hsv_image)
                cv2.drawContours(cropped_image, contour, -1, (0,255,0), 3)
                # cv2.imshow("gate",cropped_image)
                # cv2.imshow('orginal image')
            
            cv_depth = bridge.imgmsg_to_cv2(depth_msgs[time_key])
            # print(cv_depth)
            avg_depth = find_avg_gate_depth(bridge_pixels,cv_depth)
            print("the average depth is:",avg_depth)
            cv2.imshow("yote", cv_bgr)
            cv2.imshow("depth map",cv_depth)
            depth_map = Image.frombytes('F', (msg.width, msg.height), msg.data)
            depth_save = depth_map.tobytes()
            key = cv2.waitKey(10)
            # if cv2.waitKey(0) & 0xFF == ord('q'):
            #     break

cv2.destroyAllWindows()


# kernel = np.ones((5,5),np.uint8)
# tophat = cv2.morphologyEx(imgray, cv2.MORPH_TOPHAT, kernel)
# ret, thresh = cv2.threshold(tophat, 50, 255, cv2.THRESH_BINARY)
# contour, hierarchy = cv2.findContours(thresh, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
# cv2.drawContours(cropped_image, contour, -1, (0,255,0), 3)