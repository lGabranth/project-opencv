#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace cv;

/*
displayCamera() permet de vérifier qu'on récupère bien les données des fichiers xml de la librairie opencv
si on ne peut pas charger les fichiers pour la reconnaissance de visage, nez et bouche; alors on return -1;
sinon on return la variable camera_device (qui sera utilisé dans le main pour charger la caméra)
*/

int displayCamera(int argc, const char** argv, CascadeClassifier& face_cascade, CascadeClassifier& nose_cascade, CascadeClassifier& mouth_cascade) {

    CommandLineParser parser(argc, argv,
        "{help h||}"
        "{face_cascade|data/haarcascades/haarcascade_frontalface_alt.xml|Chemin de la cascade des visages.}"
        "{nose_cascade|data/haarcascades/haarcascade_mcs_nose.xml|Chemin de la cascade des nezs.}"
        "{mouth_cascade|data/haarcascades/haarcascade_mcs_mouth.xml|Chemin de la cascade des bouches.}"
        "{camera|0|Numero de la camera.}");
    parser.about("\nCe programme détecte si une personne porte son masque correctement ou non.\n\n");
    parser.printMessage();

    String face_cascade_name = samples::findFile(parser.get<String>("face_cascade"));
    String nose_cascade_name = samples::findFile(parser.get<String>("nose_cascade"));
    String mouth_cascade_name = samples::findFile(parser.get<String>("mouth_cascade"));

    // On charge toutes les "cascades"
    if (!face_cascade.load(face_cascade_name))
    {
        cout << "/!\\Erreur de chargement lors de la cascade des visages\n";
        return -1;
    };
    if (!nose_cascade.load(nose_cascade_name))
    {
        cout << "/!\\Erreur de chargement lors de la cascade des nezs\n";
        return -1;
    };
    if (!mouth_cascade.load(mouth_cascade_name))
    {
        cout << "/!\\Erreur de chargement lors de la cascade des bouches\n";
        return -1;
    };
    int camera_device;
    return camera_device = parser.get<int>("camera");
}


/* 
detectAndDisplay() permet de détecter un visage, un nez et une bouche:
si un visage est détecté alors on affiche un cercle autour de celui ci
ensuite on cherche à détecter un nez et une bouche
si un des deux est détecté alors on part du postulat que l'individu ne porte pas son masque
-> affichage du cercle en rouge avec le message "Pas de masque !"
-> sinon: affichage du cercle en vert avec le message "Masque !"
*/
void detectAndDisplay(Mat frame, CascadeClassifier& face_cascade, CascadeClassifier& nose_cascade, CascadeClassifier& mouth_cascade)
{
    Mat frame_gray;
    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    // Détection du visage
    std::vector<Rect> faces;
    face_cascade.detectMultiScale(frame_gray, faces);

    for (size_t i = 0; i < faces.size(); i++)
    {
        Mat faceROI = frame_gray(faces[i]);

        // Sur chaque visage on tente de détecter le nez et la bouche
        std::vector<Rect> nose;
        nose_cascade.detectMultiScale(faceROI, nose);
        std::vector<Rect> mouth;
        nose_cascade.detectMultiScale(faceROI, mouth);

        // Afficher du texte sur l'image
        int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
        double fontScale = 1.5;
        int thickness = 2;
        Point textOrg(100, 100);
        Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
        // Si on ne détecte ni le nez, ni la bouche ; on part du postulat que la personne porte son masque.
        // Masque = visage entouré en vert
        // Pas de masque = visage entouré en rouge
        if (nose.size() == 0 || mouth.size() == 0) {
            ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(0, 255, 0), 4);
            string someText = "Masque !";
            putText(frame, someText, textOrg, fontFace, fontScale, Scalar(0, 255, 0), thickness, 8);
        }
        else {
            ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(0, 0, 255), 4);
            string someText = "Pas de masque !";
            putText(frame, someText, textOrg, fontFace, fontScale, Scalar(0, 0, 255), thickness, 8);
        }
    }
    imshow("Capture - Detection de port du masque", frame);
}

