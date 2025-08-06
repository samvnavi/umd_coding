
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
        # cv2.rectangle(cv_bgr, (x1, y1), (x2, y2), (0, 255, 0), 2)
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
# output_dir = Path("//home/chippu/github/ComputerVision/pipe_images")


# with AnyReader([Path("/home/chippu/github/ComputerVision/mar_9_zed_pipe_rosbag")]) as reader:
with AnyReader([Path("/home/chippu/github/ComputerVision/may_4_gate_rosbag")]) as reader:

    rgb_connections = [x for x in reader.connections if x.topic == '/zed/zed_node/left/image_rect_color']
    depth_connections = [x for x in reader.connections if x.topic == '/zed/zed_node/depth/depth_registered']
    rgb_msgs = {}
    depth_msgs = {}
    count = 1
    for connection, timestamp, rawdata in reader.messages(connections = rgb_connections + depth_connections):
        if count < 1: #for pipe 1000, gor gate 1
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
            # filename_color = f"img_2025_03_09_{sec}_{nanosec}.png"
            # filepath = output_dir / filename_color
            bridge  = CvBridge()
            cv_bgr = bridge.imgmsg_to_cv2(rgb_msgs[time_key], "bgr8")
            # cv2.imwrite(str(filepath), cv_bgr)
            results = model(cv_bgr)
            detections = results[0]
            # boxes = detections.boxes
            
            boxed_img = results[0].plot()
            box = find_box(boxed_img, detections)

            if len(detections.boxes) != 0:
                # bridge_pixels = contours(boxed_img,box) #code to find individual pixels 
                
                cropped_image = cv_bgr[box[2]:box[3],box[0]:box[1]]
                hsv_image = cv2.cvtColor(cropped_image, cv2.COLOR_BGR2HSV)
                
                pixels = cropped_image.reshape((-1, 3))
                pixels = np.float32(pixels)
                k = 3
                kmeans = KMeans(n_clusters=k)
                labels = kmeans.fit_predict(pixels)
                centers = kmeans.cluster_centers_
                unique_labels, counts = np.unique(labels, return_counts=True)
                target_cluster = unique_labels[np.argmin(counts)] 

                cluster_mask = (labels == target_cluster).astype(np.uint8)
                cluster_mask = cluster_mask.reshape(cropped_image.shape[:2]) * 255
                cv2.imshow("cluster mask",cluster_mask)
                mask_hsv = cv2.bitwise_and(hsv_image,hsv_image,mask = cluster_mask)
               
                masked_image_gray = cv2.cvtColor(mask_hsv, cv2.COLOR_BGR2GRAY)
                _, thresholded_mask = cv2.threshold(masked_image_gray, 1, 255, cv2.THRESH_BINARY)
                contour, hierarchy = cv2.findContours(thresholded_mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
                #trying new code
                filtered_mask = np.zeros_like(mask_hsv)
                
                cv2.imshow("filter mask",filtered_mask)
                #changing code from here
                dst = np.zeros((cv_bgr.shape[0], cv_bgr.shape[1], 3), dtype=np.uint8)
                mask = np.zeros((cv_bgr.shape[0], cv_bgr.shape[1]), dtype=np.uint8)
                poly = []
                
                min_area = 600  # replace with your desired minimum area
                filtered_contours = [c for c in contour if cv2.contourArea(c) >= min_area]
                big_contour = sorted(filtered_contours, key=cv2.contourArea, reverse=True)[:3]

                # print(big_contour)
                for cnt in big_contour:
                    epsilon = 0.1*cv2.arcLength(cnt,True)
                    approx = cv2.approxPolyDP(cnt, epsilon, True)
                    poly.append(approx)

                
                x_offset = box[0]
                y_offset = box[2]
                for i in range(len(poly)):
                    points = poly[i].reshape(len(poly[i]), 2).tolist()
                    color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
                    cv2.drawContours(dst, poly, i, color, 1, cv2.LINE_8, hierarchy, 0)
                    for point in points:
                        full_point = (point[0] + x_offset, point[1] + y_offset)
                        cv2.circle(cv_bgr, full_point, radius=5, color=(0, 0, 255), thickness=-1)


                cv2.imshow('canvasOutput', dst)
                # cv2.drawContours(cropped_image, contour, -1, (0, 255, 0), 2)
                # #code change implemented till here
                if contour:  # make sure there are contours
                    largest_contour = max(contour, key=cv2.contourArea)
                    cv2.drawContours(cropped_image, [largest_contour], -1, 255, thickness=cv2.FILLED)
                cv2.imshow("mask",mask_hsv)
                cv2.imshow("hsv image",hsv_image)
            cv2.imshow("cv bgr",cv_bgr)

            
            cv_depth = bridge.imgmsg_to_cv2(depth_msgs[time_key])
            
            # avg_depth = find_avg_gate_depth(bridge_pixels,cv_depth)
            # print("the average depth is:",avg_depth)
          
            depth_map = Image.frombytes('F', (msg.width, msg.height), msg.data)
            depth_save = depth_map.tobytes()
            key = cv2.waitKey(10)
           

cv2.destroyAllWindows()


