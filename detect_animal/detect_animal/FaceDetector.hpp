#pragma once
// Instantiation de 3 objets de la librairie opencv
CascadeClassifier face_cascade;		// Pour le visage
CascadeClassifier nose_cascade;		// Pour le nez
CascadeClassifier mouth_cascade;	// Pour la bouche

// Déclaration des fonctions

//displayCamera()
int displayCamera(int argc, const char** argv, CascadeClassifier& face_cascade, CascadeClassifier& nose_cascade, CascadeClassifier& mouth_cascade);

//detectAndDisplay()
void detectAndDisplay(cv::Mat frame, CascadeClassifier& face_cascade, CascadeClassifier& nose_cascade, CascadeClassifier& mouth_cascade);