#include "opencv2/objdetect.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>
using namespace std;
using namespace cv;
void detectAndDisplay(Mat frame);
CascadeClassifier face_cascade;
CascadeClassifier smile_cascade;
CascadeClassifier nose_cascade;
CascadeClassifier mouth_cascade;

int main(int argc, const char** argv)
{
    CommandLineParser parser(argc, argv,
        "{help h||}"
        "{face_cascade|data/haarcascades/haarcascade_frontalface_alt.xml|Path to face cascade.}"
        "{smile_cascade|data/haarcascades/haarcascade_smile.xml|Path to smile cascade.}"
        "{nose_cascade|data/haarcascades/haarcascade_mcs_nose.xml|Path to nose cascade.}"
        "{mouth_cascade|data/haarcascades/haarcascade_mcs_mouth.xml|Path to mouth cascade.}"
        "{camera|0|Camera device number.}");
    parser.about("\nThis program demonstrates using the cv::CascadeClassifier class to detect objects (Face + eyes) in a video stream.\n"
        "You can use Haar or LBP features.\n\n");
    parser.printMessage();
    String face_cascade_name = samples::findFile(parser.get<String>("face_cascade"));
    String smile_cascade_name = samples::findFile(parser.get<String>("smile_cascade"));
    String nose_cascade_name = samples::findFile(parser.get<String>("nose_cascade"));
    String mouth_cascade_name = samples::findFile(parser.get<String>("mouth_cascade"));

    //-- 1. Load the cascades
    if (!face_cascade.load(face_cascade_name))
    {
        cout << "--(!)Error loading face cascade\n";
        return -1;
    };
    if (!smile_cascade.load(smile_cascade_name))
    {
        cout << "--(!)Error loading smile cascade\n";
        return -1;
    };
    if (!nose_cascade.load(nose_cascade_name))
    {
        cout << "--(!)Error loading nose cascade\n";
        return -1;
    };
    if (!mouth_cascade.load(mouth_cascade_name))
    {
        cout << "--(!)Error loading mouth cascade\n";
        return -1;
    };
    int camera_device = parser.get<int>("camera");
    VideoCapture capture;
    //-- 2. Read the video stream
    capture.open(camera_device);
    if (!capture.isOpened())
    {
        cout << "--(!)Error opening video capture\n";
        return -1;
    }
    Mat frame;
    while (capture.read(frame))
    {
        if (frame.empty())
        {
            cout << "--(!) No captured frame -- Break!\n";
            break;
        }
        //-- 3. Apply the classifier to the frame
        detectAndDisplay(frame);
        if (waitKey(10) == 27)
        {
            break; // escape
        }
    }
    return 0;
}
void detectAndDisplay(Mat frame)
{
    Mat frame_gray;
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);
    //-- Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces);
    Scalar *t = new Scalar;
    

    for (size_t i = 0; i < faces.size(); i++)
    {
        Mat faceROI = frame_gray(faces[i]);
        //-- In each face, detect eyes
        std::vector<Rect> nose;
        nose_cascade.detectMultiScale(faceROI, nose);
        std::vector<Rect> mouth;
        mouth_cascade.detectMultiScale(faceROI, mouth);

        Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        if (nose.size() == 0) {
            ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(0, 255, 0), 4);
        }
        else {
            ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(0, 0, 255), 4);
        }
        //ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, color, 4);



    }

    //-- Show what you got
    imshow("Capture - Face detection", frame);
}