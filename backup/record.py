import cv2

# Open a connection to the camera (0 is typically the default camera)
cap = cv2.VideoCapture(0)

# Check if the camera is opened successfully
if not cap.isOpened():
    print("Error: Could not open camera.")
    exit()

# Get the video frame width and height
frame_width = int(cap.get(3))  # Width of the frame
frame_height = int(cap.get(4))  # Height of the frame

# Define the codec and create VideoWriter object
# 'XVID' is the codec, you can choose different codecs (e.g. 'MJPG', 'MP4V', etc.)
fourcc = cv2.VideoWriter_fourcc(*'XVID')  # You can change the codec here
out = cv2.VideoWriter('output.avi', fourcc, 20.0, (frame_width, frame_height))

# Capture video frames until the user presses 'q'
while True:
    # Read a frame from the camera
    ret, frame = cap.read()
    
    # If the frame was read successfully, display and write it
    if ret:
        # Write the frame to the output video file
        out.write(frame)
        
        # Display the frame in a window
        cv2.imshow('Camera', frame)

    # Wait for the user to press 'q' to quit
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Release the camera and writer, and close all OpenCV windows
cap.release()
out.release()
cv2.destroyAllWindows()
