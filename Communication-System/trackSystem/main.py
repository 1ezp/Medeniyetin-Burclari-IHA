from data import *
import cv2

# Global variables to store the target selection and tracker
target_bbox = (0, 0, 0, 0)
target_selected = False
tracker_initialized = False

mouse_x, mouse_y = -1, -1
square_size = 50  



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
        Target.update({"x":-1,"y":-1})
        target_selected = False
        target_bbox = (0, 0, 0, 0)
        tracker_initialized = False







def main():
    global target_selected, target_bbox, tracker_initialized,mouse_x, mouse_y, square_size
    cap = cv2.VideoCapture('http://192.168.10.110:80/stream')
    #cap = cv2.VideoCapture(0)

    if not cap.isOpened():
        print("Error: Could not open video.")
        exit()
    cv2.namedWindow('Video')
    cv2.setMouseCallback('Video', select_target)
    # Create a tracker object
    tracker = cv2.TrackerCSRT_create() 
    while cap.isOpened():
        ret, frame = cap.read()
        if not ret or frame is None or frame.size == 0:
            print("Error: Failed to read video frame.")
            break

        if target_selected and not tracker_initialized:

            # Re-initialize the tracker with the current frame and new bounding box
            #tracker = cv2.TrackerCSRT_create()
            tracker.init(frame, target_bbox)
            tracker_initialized = True
            target_selected = False

        # Ensure the frame is valid before updating the tracker
        if tracker_initialized:
            ret, bbox = tracker.update(frame)
            if ret:
                # Tracking
                p1 = (int(bbox[0]), int(bbox[1]))
                p2 = (int(bbox[0] + bbox[2]), int(bbox[1] + bbox[3]))
                cv2.rectangle(frame, p1, p2, (255, 0, 0), 2, 1)
                cv2.putText(frame, f'X: {int(bbox[0])}, Y: {int(bbox[1])}', (20, 40), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 1)
                Target.update({"x":int(bbox[0]),"y":int(bbox[1])})
            else:
                pass
                # Tracking failure
                ##cv2.putText(frame, "Tracking failure detected", (20, 80), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

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
if __name__ == "__main__":
    main()