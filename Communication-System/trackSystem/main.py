from data import Target, CAMERA
import cv2
from threading import Thread, Lock
import time

class VideoTracker:
    def __init__(self, stream_url, square_size=130):
        self.stream_url = stream_url
        self.square_size = square_size
        self.target_bbox = (0, 0, 0, 0)
        self.target_selected = False
        self.tracker_initialized = False
        self.mouse_x, mouse_y = -1, -1
        self.fps = 0
        self.data_lock = Lock()
        self.frame_lock = Lock()
        self.current_frame = None
        self.tracker = cv2.TrackerCSRT_create()
    
    def get_screen_resolution(self):
        window_name = "Video"
        cv2.namedWindow(window_name, cv2.WINDOW_NORMAL)
        cv2.setWindowProperty(window_name, cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
        time.sleep(0.1)
        
        screen_width = cv2.getWindowImageRect(window_name)[2]
        screen_height = cv2.getWindowImageRect(window_name)[3]
        cv2.destroyWindow(window_name)
        return screen_width, screen_height
    
    def select_target(self, event, x, y, flags, param):
        
        if event == cv2.EVENT_MOUSEMOVE:
            self.mouse_x, self.mouse_y = x, y
        
        elif event == cv2.EVENT_LBUTTONDOWN:
            self.target_bbox = (x - self.square_size // 2, y - self.square_size // 2, self.square_size, self.square_size)
            
            self.target_selected = True
            self.tracker_initialized = False  
        
        elif event == cv2.EVENT_RBUTTONDOWN:
            with self.data_lock:
                Target.update({"x": -1, "y": -1})
            self.target_selected = False
            self.target_bbox = (0, 0, 0, 0)
            self.tracker_initialized = False
    
    def draw_crosshair(self, frame, x, y, size=100):
        line_thickness = 2
        color = (0, 0, 255)
        cv2.line(frame, (x - size // 2, y - size // 2), (x - size // 4, y - size // 2), color, line_thickness)
        cv2.line(frame, (x - size // 2, y - size // 2), (x - size // 2, y - size // 4), color, line_thickness)
        cv2.line(frame, (x + size // 2, y - size // 2), (x + size // 4, y - size // 2), color, line_thickness)
        cv2.line(frame, (x + size // 2, y - size // 2), (x + size // 2, y - size // 4), color, line_thickness)
        cv2.line(frame, (x - size // 2, y + size // 2), (x - size // 4, y + size // 2), color, line_thickness)
        cv2.line(frame, (x - size // 2, y + size // 2), (x - size // 2, y + size // 4), color, line_thickness)
        cv2.line(frame, (x + size // 2, y + size // 2), (x + size // 4, y + size // 2), color, line_thickness)
        cv2.line(frame, (x + size // 2, y + size // 2), (x + size // 2, y + size // 4), color, line_thickness)

    
    def video_capture(self):
        cap = cv2.VideoCapture(self.stream_url)
        
        if not cap.isOpened():
            print("Error: Could not open video.")
            return
        
        prev_time = time.time()
        while cap.isOpened():
            ret, frame = cap.read()
            if ret and frame is not None:
                with self.frame_lock:
                    self.current_frame = frame
            current_time = time.time()
            self.fps = 1 / (current_time - prev_time) if current_time - prev_time > 0 else 0
            prev_time = current_time
            time.sleep(0.01)

        cap.release()
    
    def capture_video(self):
        screen_width, screen_height = self.get_screen_resolution()

        cv2.namedWindow('Video', cv2.WINDOW_NORMAL)
        cv2.setWindowProperty('Video', cv2.WND_PROP_FULLSCREEN, cv2.WINDOW_FULLSCREEN)
        cv2.setMouseCallback('Video', self.select_target)

        while True:
            with self.frame_lock:
                frame = self.current_frame.copy() if self.current_frame is not None else None
            
            if frame is None:
                time.sleep(0.01)
                continue

            frame = cv2.resize(frame, (screen_width, screen_height))

            if self.target_selected and not self.tracker_initialized:
                self.tracker = cv2.TrackerCSRT_create() 
                self.tracker.init(frame, self.target_bbox)
                self.tracker_initialized = True
                self.target_selected = False

            if self.tracker_initialized and self.tracker:
                ret, bbox = self.tracker.update(frame)
                if ret:
                    p1 = (int(bbox[0]), int(bbox[1]))
                    p2 = (int(bbox[0] + bbox[2]), int(bbox[1] + bbox[3]))
                    cv2.rectangle(frame, p1, p2, (255, 0, 0), 2, 1)
                    cv2.putText(frame, f'X: {int(bbox[0])}, Y: {int(bbox[1])}', (20, 40), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 1)
                    with self.data_lock:
                        Target.update({"x": int(bbox[0]), "y": int(bbox[1])})
                else:
                    with self.data_lock:
                        Target.update({"x": -1, "y": -1})
                    self.target_selected = False
                    self.target_bbox = (0, 0, 0, 0)
                    self.tracker_initialized = False
                    cv2.putText(frame, "Tracking failure", (20, 80), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

            if self.mouse_x != -1 and self.mouse_y != -1:
                self.draw_crosshair(frame, self.mouse_x, self.mouse_y, self.square_size)

            with self.data_lock:
                cv2.putText(frame, f'FPS: {int(self.fps)}', (20, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 1)
            
            cv2.imshow('Video', frame)
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

        cv2.destroyAllWindows()
    
    def start(self):
        Thread(target=self.video_capture).start()
        self.capture_video()
    