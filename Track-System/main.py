import cv2

# Global variables to store the target selection and tracker
target_selected = False
target_bbox = (0, 0, 0, 0)
tracker_initialized = False

mouse_x, mouse_y = -1, -1
square_size = 50  

cap = cv2.VideoCapture('http://192.168.137.24:81/stream')
#cap = cv2.VideoCapture(0)

if not cap.isOpened():
    print("Error: Could not open video.")
    exit()

def select_target(event, x, y, flags, param):
    global target_selected, target_bbox, tracker_initialized,mouse_x, mouse_y, square_size
    
    if event == cv2.EVENT_MOUSEMOVE:
        mouse_x, mouse_y = x, y
        
    elif event == cv2.EVENT_MOUSEWHEEL:
        if flags > 0:  # Scroll up
            square_size = square_size + 5
        else:  
            square_size = square_size - 5

    elif event == cv2.EVENT_LBUTTONDOWN:
        target_bbox = (x - square_size // 2, y - square_size // 2, square_size, square_size)  
        target_selected = True
        tracker_initialized = False  
        
    elif  event == cv2.EVENT_RBUTTONDOWN:
        target_selected = False
        target_bbox = (0, 0, 0, 0)
        tracker_initialized = False



cv2.namedWindow('Video')
cv2.setMouseCallback('Video', select_target)



tracker = cv2.TrackerCSRT_create()  # TrackerKCF, TrackerMIL, etc.


while cap.isOpened():
    ret, frame = cap.read()
    if not ret or frame is None or frame.size == 0:
        print("Error: Failed to read video frame.")
        break

    if target_selected and not tracker_initialized:

        # Re-initialize the tracker with the current frame and new bounding box
        tracker = cv2.TrackerCSRT_create()
        tracker.init(frame, target_bbox)
        tracker_initialized = True
        target_selected = False

    # Ensure the frame is valid before updating the tracker
    if tracker_initialized:
        ret, bbox = tracker.update(frame)

        if ret:
            # Tracking success
            p1 = (int(bbox[0]), int(bbox[1]))
            p2 = (int(bbox[0] + bbox[2]), int(bbox[1] + bbox[3]))
            cv2.rectangle(frame, p1, p2, (255, 0, 0), 2, 1)
            # Draw the coordinates on the frame
            cv2.putText(frame, f'X: {int(bbox[0])}, Y: {int(bbox[1])}', (20, 40), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        else:
            # Tracking failure
            cv2.putText(frame, "Tracking failure detected", (20, 80), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

    # Draw the square around the mouse cursor
    if mouse_x != -1 and mouse_y != -1:
        top_left = (mouse_x - square_size // 2, mouse_y - square_size // 2)
        bottom_right = (mouse_x + square_size // 2, mouse_y + square_size // 2)
        cv2.rectangle(frame, top_left, bottom_right, (0, 255, 0), 2)

    cv2.imshow('Video', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
