from data import Target, CAMERA
import cv2
import time
import requests

# Global variables to store the target selection and tracker
target_bbox = (0, 0, 0, 0)
target_selected = False
tracker_initialized = False

mouse_x, mouse_y = -1, -1
square_size = 130

def get_screen_resolution():
    window_name = "Video"
    cv2.namedWindow(window_name, cv2.WINDOW_NORMAL)
    cv2.setWindowProperty(window_name, cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
    time.sleep(0.1)
    
    screen_width = cv2.getWindowImageRect(window_name)[2]
    screen_height = cv2.getWindowImageRect(window_name)[3]
    cv2.destroyWindow(window_name)
    return screen_width, screen_height

screen_width, screen_height = get_screen_resolution()
CAMERA.update({"weight": screen_width, "height": screen_height})
print(CAMERA)

def select_target(event, x, y, flags, param):
    global target_selected, target_bbox, tracker_initialized, mouse_x, mouse_y, square_size
    
    if event == cv2.EVENT_MOUSEMOVE:
        mouse_x, mouse_y = x, y
        
    # elif event == cv2.EVENT_MOUSEWHEEL:
    #     if flags > 0:  # Scroll up
    #         square_size = square_size + 5
    #     else:  
    #         square_size = square_size - 5

    elif event == cv2.EVENT_LBUTTONDOWN:
        target_bbox = (x - square_size // 2, y - square_size // 2, square_size, square_size)  
        target_selected = True
        tracker_initialized = False
        
    elif event == cv2.EVENT_RBUTTONDOWN:
        Target.update({"x": -1, "y": -1})
        target_selected = False
        target_bbox = (0, 0, 0, 0)
        tracker_initialized = False


def draw_crosshair(frame, x, y, size=100):
    line_thickness = 2
    color = (0, 0, 255)
    # Top-left corner
    cv2.line(frame, (x - size // 2, y - size // 2), (x - size // 4, y - size // 2), color, line_thickness)
    cv2.line(frame, (x - size // 2, y - size // 2), (x - size // 2, y - size // 4), color, line_thickness)
    
    # Top-right corner
    cv2.line(frame, (x + size // 2, y - size // 2), (x + size // 4, y - size // 2), color, line_thickness)
    cv2.line(frame, (x + size // 2, y - size // 2), (x + size // 2, y - size // 4), color, line_thickness)
    
    # Bottom-left corner
    cv2.line(frame, (x - size // 2, y + size // 2), (x - size // 4, y + size // 2), color, line_thickness)
    cv2.line(frame, (x - size // 2, y + size // 2), (x - size // 2, y + size // 4), color, line_thickness)
    
    # Bottom-right corner
    cv2.line(frame, (x + size // 2, y + size // 2), (x + size // 4, y + size // 2), color, line_thickness)
    cv2.line(frame, (x + size // 2, y + size // 2), (x + size // 2, y + size // 4), color, line_thickness)





def main():
    global target_selected, target_bbox, tracker_initialized, mouse_x, mouse_y, square_size
    
    cap = cv2.VideoCapture(0)
    #requests.get("http://192.168.10.60/set?framesize=7")
    # cap = cv2.VideoCapture("https://192.168.10.60/stream")
    
    
    if not cap.isOpened():
        print("Error: Could not open video.")
        exit()
    
    cv2.namedWindow('Video', cv2.WINDOW_NORMAL)
    time.sleep(0.1)
    cv2.setWindowProperty('Video', cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
    cv2.setMouseCallback('Video', select_target)

    while cap.isOpened():
        ret, frame = cap.read()
        if not ret or frame is None or frame.size == 0:
            print("Error: Failed to read video frame.")
            break

        frame = cv2.resize(frame, (screen_width, screen_height))

        if target_selected and not tracker_initialized:
            tracker = cv2.TrackerCSRT_create() 
            tracker.init(frame, target_bbox)
            tracker_initialized = True
            target_selected = False

        if tracker_initialized:
            ret, bbox = tracker.update(frame)
            if ret:
                p1 = (int(bbox[0]), int(bbox[1]))
                p2 = (int(bbox[0] + bbox[2]), int(bbox[1] + bbox[3]))
                cv2.rectangle(frame, p1, p2, (255, 0, 0), 2, 1)
                cv2.putText(frame, f'X: {int(bbox[0])}, Y: {int(bbox[1])}', (20, 40), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 1)
                Target.update({"x": int(bbox[0]), "y": int(bbox[1])})
            else:
                Target.update({"x": -1, "y": -1})
                target_selected = False
                target_bbox = (0, 0, 0, 0)
                tracker_initialized = False
                cv2.putText(frame, "Tracking failure detected", (20, 80), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

        if mouse_x != -1 and mouse_y != -1:
            draw_crosshair(frame, mouse_x, mouse_y, square_size)
            # top_left = (mouse_x - square_size // 2, mouse_y - square_size // 2)
            # bottom_right = (mouse_x + square_size // 2, mouse_y + square_size // 2)
            # cv2.rectangle(frame, top_left, bottom_right, (0, 255, 0), 2)
        
        cv2.imshow('Video', frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
