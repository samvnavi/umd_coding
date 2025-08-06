import cv2
import numpy as np
from scipy.spatial.transform import Rotation as R
from ultralytics import YOLO

def draw_lines(gate_img, gate_pixel_points):
    thick = 2
    color = (0,255,0)
    pt1 = tuple(gate_pixel_points[0].astype(int))
    pt2 = tuple(gate_pixel_points[1].astype(int))
    pt3 = tuple(gate_pixel_points[2].astype(int))
    pt4 = tuple(gate_pixel_points[3].astype(int))
    cv2.line(gate_img,pt1,pt2,color,thick)
    cv2.line(gate_img,pt3,pt4,color,thick)
    cv2.line(gate_img,pt1,pt3,color,thick)
    cv2.line(gate_img,pt2,pt4,color,thick)
    
file_name = "/home/chippu/github/ComputerVision/translation_perpendicular/gate_left_120_40.jpg"

lateral_val = 40
depth_val = 120


gate_img = cv2.imread(file_name)
K = np.array(
        [[ 476.703010, -0.210070584,  492.074478],
        [ 0,  476.263431,  296.957337],
        [ 0, 0,  1]])

D = np.array(
    [[-0.06644421],
     [ 0.01148719],
     [-0.02155796],
     [0.00743725]]
)
gate_height = 1.4732
gate_width = 2.159 

img = cv2.imread(file_name)

            
            
# find_real_distance(file_name)
    
gate_object_points = np.array([
    [gate_width / 2, gate_height / 2, 0], # bottom right
    [-gate_width / 2, gate_height / 2, 0], # bottom left
    [gate_width / 2, -gate_height / 2, 0], # top right
    [-gate_width / 2, -gate_height / 2, 0] # top left
], dtype=np.float32)


# file_name = ""/home/chippu/github/ComputerVision/angles/gate_left3.jpg"
gate_pixel_points = np.array([
    [399,313],
    [146, 329],
    [389,139],
    [152,164]
], dtype=np.float32)


for i in gate_pixel_points:
    x,y = int(i[0]),int(i[1])
    gate_img[y,x] = (0, 255, 127)

draw_lines(gate_img,gate_pixel_points)
# cv2.imshow("gate image",gate_img)
# cv2.waitKey(0)
# gate_pixel_points = np.roll(gate_pixel_points, 2)

success, rvec, tvec = cv2.solvePnP(
    gate_object_points,
    gate_pixel_points,
    K, D
)

est_rot_mat, _ = cv2.Rodrigues(rvec)
est_rot_eul = R.from_matrix(est_rot_mat).as_euler('xyz', True)
distance = np.linalg.norm(tvec)

print(f"measured depth (z axis) distance = {depth_val}")
print(f" distance along the z axis = {tvec[2]* 39.3700787}")
print(f"measured lateral distance = {lateral_val}")
print(f"lateral distance shift = {tvec[0]* 39.3700787}")

print(f"total distance from camera to origin = {distance * 39.3700787}")

print(f"{est_rot_eul=}")
print(f"{tvec=}")

#  39.3700787
# Define axis in 3D (origin and endpoints of X, Y, Z axes)
# draw axis
axis_length = 5
axes_3D = np.float32([
    [0, 0, 0],
    [axis_length, 0, 0],
    [0,axis_length, 0],
    [0, 0, axis_length]
])


imgpts, _ = cv2.projectPoints(axes_3D, rvec, tvec, K, D)
imgpts = np.int32(imgpts).reshape(-1, 2)

origin = tuple(imgpts[0])
cv2.line(gate_img, origin, tuple(imgpts[1]), (0, 0, 255), 3)  # X - red
cv2.line(gate_img, origin, tuple(imgpts[2]), (0, 255, 0), 3)  # Y - green
cv2.line(gate_img, origin, tuple(imgpts[3]), (255, 0, 0), 3)  # Z - blue
cv2.imshow("trans_perpendicular: gate_left_120_40", gate_img)
cv2.waitKey(0)
cv2.destroyAllWindows()


# file_name = ""/home/chippu/github/ComputerVision/angles/gate_left3.jpg"
# gate_pixel_points = np.array([
#     [558,413],
#     [346, 410],
#     [560,267],
#     [361,268]
# ], dtype=np.float32)

# file_name = ""/home/chippu/github/ComputerVision/angles/gate_left2.jpg"
# gate_pixel_points = np.array([
#     [532,411],
#     [318, 415],
#     [530,266],
#     [329,272]
# ], dtype=np.float32)

# # file_name = ""/home/chippu/github/ComputerVision/angles/gate_left3.jpg"
# gate_pixel_points = np.array([
#     [513,337],
#     [186, 355],
#     [511,127],
#     [197,120]
# ], dtype=np.float32)

# file_name = ""/home/chippu/github/ComputerVision/angles/gate_right2.jpg"
# gate_pixel_points = np.array([
#     [536,425],
#     [318, 426],
#     [533,277],
#     [330,283]
# ], dtype=np.float32)

# file_name = ""/home/chippu/github/ComputerVision/gate_left_102.jpg"
# gate_pixel_points = np.array([
#     [448,366],
#     [140, 374],
#     [437,152],
#     [148,178]
# ], dtype=np.float32)


# file_name = ""/home/chippu/github/ComputerVision/angles/gate_right1.jpg"
# gate_pixel_points = np.array([
#     [624,414],
#     [413, 427],
#     [618,263],
#     [420,282]
# ], dtype=np.float32)
# file_name = ""/home/chippu/github/ComputerVision/gate_left0.jpg"
# gate_pixel_points = np.array([
#     [220,392],
#     [13, 406],
#     [201,246],
#     [6,254]
# ], dtype=np.float32)
# file_name = ""/home/chippu/github/ComputerVision/angles/gate_left1.jpg"
# gate_pixel_points = np.array([
#     [617,401],
#     [411, 415],
#     [611,254],
#     [418,272]
# ], dtype=np.float32)
# file_name = ""/home/chippu/github/ComputerVision/gate_right_63.jpg"
# gate_pixel_points = np.array([
#     [467,415],
#     [33, 396],
#     [462,91],
#     [60,126]
# ], dtype=np.float32)

# file_name = "/home/chippu/github/ComputerVision/gate_left_130.jpg"
# gate_pixel_points = np.array([
#     [409,311],
#     [183, 319],
#     [406,159],
#     [190,167]
# ], dtype=np.float32)

