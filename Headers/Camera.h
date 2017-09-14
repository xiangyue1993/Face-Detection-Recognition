#ifndef CAMERA_
#define CAMERA_
#include <opencv2\opencv.hpp>

using namespace cv;

class Camera
{
public:
	Camera();
	~Camera();

private:
	VideoCapture* cam;

public:
	void OpenCamera();
	cv::Mat ReadCamera();
	void CloseCamera();
	bool IsCameraOpen();
};

#endif
