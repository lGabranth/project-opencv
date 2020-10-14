#include <opencv2/opencv.hpp>  
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    cv::VideoCapture video_capture;
    if (!video_capture.open(0)) {
        return 0;
    }

    Mat frame;

    while (true) {
        video_capture >> frame;

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