#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace cv;
#include "FaceDetector.hpp"

int main(int argc, const char** argv)
{
    VideoCapture capture;
    
    int camera_device = cascadeClassifier(argc, argv, face_cascade, nose_cascade, mouth_cascade);
    if (camera_device != -1)
    {
        // On lit le stream vid�o
        capture.open(camera_device);
    }

    if (!capture.isOpened())
    {
        cout << "/!\\Erreur lors de l'ouverture de la camera\n";
        return -1;
    }

    Mat frame;

    while (capture.read(frame))
    {
        if (frame.empty())
        {
            cout << "/!\\Pas d'image capturee\n";
            break;
        }
        // Traitement de la vid�o
        detectAndDisplay(frame, face_cascade, nose_cascade, mouth_cascade);
        // Si on appuie sur le bouton "esc" pendant la vid�o, on quitte cette derni�re.
        if (waitKey(10) == 27)
        {
            break;
        }
    }
    return 0;
}