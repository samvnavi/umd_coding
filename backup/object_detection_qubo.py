#!/usr/bin/env python
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Vector3
from vision_msgs.msg import BoundingBox2D, BoundingBox2DArray, Pose2D, Point2D
import message_filters
from sensor_msgs.msg import Image
from rclpy.qos import qos_profile_sensor_data
import cv2
from cv_bridge import CvBridge
import numpy as np
from ultralytics import YOLO
import sys

# ros2 run qubo object_detection.py [true]

class ObjectDetection(Node):
    def __init__(self, show):
        super().__init__("object_detection_node")

        self.show = show
        self.model = YOLO('gate_object_detection_model.pt')
        self.boxed_img = None
        self.get_logger().info("Finished Loading Model")

        # self.subscription_color = self.create_subscription(
        #     Image,
        #     "/zed/zed_node/left/image_rect_color",
        #     self.detect_objects,
        #     qos_profile = qos_profile_sensor_data
        # )
        # self.subscription_depth_map = self.create_subscription(
        #     Image,
        #     "/zed/zed_node/depth/depth_registered",
        #     self.detect_objects,
        #     qos_profile = qos_profile_sensor_data
        # )
        depth_sub = message_filters.Subscriber(
            self, 
            Image, 
            "/zed/zed_node/depth/depth_registered", 
            qos_profile_sensor_data
        )
        color_sub = message_filters.Subscriber(
            self, 
            Image, 
            "/zed/zed_node/left/image_rect_color", 
            qos_profile_sensor_data
        )
        self.bridge = CvBridge()
        self.boxes_pub = self.create_publisher(
            BoundingBox2DArray,
            '/object_detections',
            1
        )
        self.gate_pub = self.create_publisher(
            Vector3,
            '/gate_bbox',
            1
        )
        self.distance = self.create_publisher(
            Vector3,
            '/gate_distance',
            1
        )
        self.ts = message_filters.ApproximateTimeSynchronizer(
            [color_sub,depth_sub], 
            queue_size=10, 
            slop=0.5, 
            allow_headerless=True)
        self.ts.registerCallback(self.detect_objects)

    def detect_objects(self, color_msg : Image,depth_msg: Image):
        color_img = self.bridge.imgmsg_to_cv2(color_msg)
        depth_img = self.bridge.imgmsg_to_cv2(depth_msg)
        result = self.model(color_img)[0]
        sef.bo
        bboxes = BoundingBox2DArray()
        gate_found = False
        for box in result.boxes:
            box_class = self.model.names[box.data[0][5].item()]
            print(box_class)
            
            corner1 = (int(box.xyxy[0][0].item()), int(box.xyxy[0][1].item()))
            corner2 = (int(box.xyxy[0][2].item()), int(box.xyxy[0][3].item()))
            cv2.rectangle(color_img, corner1, corner2, (0, 255, 255), 3)
            cv2.putText(color_img, box_class, corner1, cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 0), 1, cv2.LINE_AA)
            
            s_x = box.xywh[0][0].item()
            s_y = box.xywh[0][1].item()
            s_w = box.xywh[0][2].item()
            s_h = box.xywh[0][3].item()

            bbox = BoundingBox2D(
            center = Pose2D(
                position = Point2D(
                    x = s_x,
                    y = s_y
                ),
                theta = 0.0
            ),
            size_x = s_w,
            size_y = s_h
            )
            bboxes.boxes.append(bbox)
            
            if box_class == "gate" and not gate_found:
                self.gate_pub.publish(bbox)
                gate_found = True
                

        if self.show:
            cv2.imshow('object detections', color_img)
            cv2.waitKey(1)
        
        self.boxes_pub.publish(bboxes)
    
    counter = 1
    def contours(self,box_image,box):
        bridge_pixels = []
        for y in range(box[2],box[3]):
            for x in range(box[0],box[1]):
                pixel_color = box_image[y][x]
                if (pixel_color[0]>= 80 and pixel_color[0]<= 140 and pixel_color[1]>= 90 and pixel_color[1]<= 150 and pixel_color[2]>= 50 and pixel_color[2]<= 130 ):
                    box_image[y,x] = [0,255, 0]
                    bridge_pixels.append([y,x])
        return bridge_pixels
    
    def find_box(self,boxed_img,detections):
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
        
    def find_avg_gate_depth(self,bridge_pixels,cv_depth):
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

def main(args):
    show = False
    if len(args) > 1:
        show = bool(args[1])
    rclpy.init()
    object_detection_node = ObjectDetection(show)
    rclpy.spin(object_detection_node)

if __name__ == "__main__":
    main(sys.argv)
