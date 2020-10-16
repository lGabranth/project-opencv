#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace cv;
#include "FaceDetector.hpp"

int main(int argc, const char** argv)
{
    VideoCapture capture;
    
    // récupération du return de la fonction displayCamera
    int camera_device = displayCamera(argc, argv, face_cascade, nose_cascade, mouth_cascade);
    if (camera_device != -1)
    {
        capture.open(camera_device); // On lit le stream vidéo
    }

    if (!capture.isOpened())
    {
        cout << "/!\\Erreur lors de l'ouverture de la camera\n";
        return -1;
    }

    Mat frame;

    while (capture.read(frame)) //Pendant que on lit la video de la caméra
    {
        if (frame.empty())
        {
            cout << "/!\\Pas d'image capturee\n";
            break;
        }
        // Traitement de la vidéo suivant la fonction detectAndDisplay
        detectAndDisplay(frame, face_cascade, nose_cascade, mouth_cascade);
        // Si on appuie sur le bouton "esc" pendant la vidéo, on quitte cette dernière.
        if (waitKey(10) == 27)
        {
            break;
        }
    }
    return 0;
}