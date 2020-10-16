#pragma once
CascadeClassifier face_cascade;
CascadeClassifier nose_cascade;
CascadeClassifier mouth_cascade;

int cascadeClassifier(int argc, const char** argv, CascadeClassifier& face_cascade, CascadeClassifier& nose_cascade, CascadeClassifier& mouth_cascade);
void detectAndDisplay(cv::Mat frame, CascadeClassifier& face_cascade, CascadeClassifier& nose_cascade, CascadeClassifier& mouth_cascade);