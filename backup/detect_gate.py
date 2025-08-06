import roboflow
import json 

import numpy as np
import cv2
import os

def check_yellow(gate_img):
    lower_yellow = np.array([20, 100, 100])
    upper_yellow = np.array([30, 255, 255])
    # Create a mask for yellow color
    img_hsv = cv2.cvtColor(gate_img, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(img_hsv, lower_yellow, upper_yellow) # sets mask to 225 if the colur is there 
    return np.any(mask)

def find_gate_imgs():
    count = 0
    for dirpath, dirnames, filenames in os.walk('/home/chippu/github/ComputerVision/gate_pics'):
            for img in filenames:
                file_path = os.path.join(dirpath, img)
                gate_img  = cv2.imread(file_path)
                if gate_img is None:
                    print(f"Failed to load image: {file_path}")
                    continue  # Skip this image and move to the next one
                else:
                    # is_yellow = check_yellow(gate_img)
                    if (count == 100):
                        return
                    else:
                        count += 1
                        cv2.imshow('img',gate_img)
                        project.upload(file_path)
                        cv2.waitKey(100)
                        print(count)
                    


roboflow.login()
{
  "name": "qubogate",
  "url": "qubogate",
  "projects": [
    "qubogate/gate-detection-aq6eu"
  ]
}
rf = roboflow.Roboflow(api_key="9Ggb5fB5YkqlXwb0aKUK")
workspace = rf.workspace()
workspaceId = 'qubogate'
projectId = 'qubogate/gate-detection-aq6eu'
project = rf.workspace().project("gate-detection-aq6eu")
# Upload the image to your project
find_gate_imgs()
cv2.destroyAllWindows()
