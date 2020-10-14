#include <opencv2/opencv.hpp>  
#include <iostream>
#include "FaceDetector.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    cv::VideoCapture video_capture;
    if (!video_capture.open(0)) {
        return 0;
    }
    FaceDetector face_detector;
    cv::Mat frame;
    while (true) {
        video_capture >> frame;
        auto rectangles = face_detector.detect_face_rectangles(frame);
        cv::Scalar color(0, 105, 205);
        int frame_thickness = 4;
        for (const auto& r : rectangles) {
            cv::rectangle(frame, r, color, frame_thickness);
        }
        imshow("Image", frame);
        const int esc_key = 27;
        if (cv::waitKey(10) == esc_key) {
            break;
        }

        // Boucle pour prendre une i photos de la videocapture
        for (int i = 0; i < 20; i++) {
            string name = "Capture_from_video" + to_string(i) + ".png";
            imwrite("../../img/" + name, frame);
            cout << "A screen ! \n";
        }

        if (waitKey(1) >= 0) break;
    }
    cv::destroyAllWindows();
    video_capture.release();
    return 0;
}