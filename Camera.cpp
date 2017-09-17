#include "Headers/Camera.h"

Camera::Camera()
{
	this->cam = new VideoCapture();
}

void Camera::OpenCamera(){
	if (!cam->isOpened()){
		cam->open(0);
	}
}

cv::Mat Camera::ReadCamera(){
	cv::Mat frame;

	if (cam->isOpened()){
		(*cam) >> frame;
	}

	return frame;
}

void Camera::CloseCamera(){
	if (cam->isOpened())
		cam->release();
}

bool Camera::IsCameraOpen(){
	if (cam->isOpened()) return true;

	return false;
}

Camera::~Camera()
{
	
}
