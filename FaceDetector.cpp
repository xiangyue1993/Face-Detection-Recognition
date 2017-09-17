#include "Headers/FaceDetector.h"
//LibFaceDetection are required, refer to https://github.com/ShiqiYu/libfacedetection
#include "facedetect-dll.h"

//#pragma comment(lib,"libfacedetect.lib")
#pragma comment(lib,"libfacedetect-x64.lib")

//define the buffer size. Do not change the size!
#define DETECT_BUFFER_SIZE 0x20000

using namespace cv;

std::vector<SingleFaceInfo> FaceDetector::FaceDetection(Mat &SrcImg){
	Mat img_gray;
	Mat result_multiview_reinforce = SrcImg.clone();;
	std::vector<SingleFaceInfo> faces;

	cvtColor(SrcImg, img_gray, CV_BGR2GRAY);  //RGBtoGray
	int * pResults = NULL;
	//pBuffer is used in the detection functions.

	unsigned char * pBuffer = (unsigned char *)malloc(DETECT_BUFFER_SIZE);

	int doLandmark = 1;
	pResults = facedetect_multiview_reinforce(pBuffer, (unsigned char*)(img_gray.ptr(0)), img_gray.cols, img_gray.rows, (int)img_gray.step,
		1.2f, 3, 48, 0, doLandmark);
	for (int i = 0; i < (pResults ? *pResults : 0); i++)
	{
		short * p = ((short*)(pResults + 1)) + 142 * i;
		int x = p[0];
		int y = p[1];
		int w = p[2];
		int h = p[3];

		Rect singlefaceloc(x, y, w, h);

		std::vector<Point2f> facial5points;

		//Landmark of eye starts from 36~47
		int average_lefteye_x = ((int)p[6 + 2 * 36] + (int)p[6 + 2 * 37] + (int)p[6 + 2 * 38] +
			(int)p[6 + 2 * 39] + (int)p[6 + 2 * 40] + (int)p[6 + 2 * 41]) / 6;
		int average_lefteye_y = ((int)p[6 + 2 * 36 + 1] + (int)p[6 + 2 * 37 + 1] + (int)p[6 + 2 * 38 + 1] +
			(int)p[6 + 2 * 39 + 1] + (int)p[6 + 2 * 40 + 1] + (int)p[6 + 2 * 41 + 1]) / 6;
		int average_righteye_x = ((int)p[6 + 2 * 42] + (int)p[6 + 2 * 43] + (int)p[6 + 2 * 44] +
			(int)p[6 + 2 * 45] + (int)p[6 + 2 * 46] + (int)p[6 + 2 * 47]) / 6;
		int average_righteye_y = ((int)p[6 + 2 * 42 + 1] + (int)p[6 + 2 * 43 + 1] + (int)p[6 + 2 * 44 + 1] +
			(int)p[6 + 2 * 45 + 1] + (int)p[6 + 2 * 46 + 1] + (int)p[6 + 2 * 47 + 1]) / 6;
		facial5points.push_back(Point2f(average_lefteye_x, average_lefteye_y));
		facial5points.push_back(Point2f(average_righteye_x, average_righteye_y));

		int nose_x = (int)p[6 + 2 * 30];
		int nose_y = (int)p[6 + 2 * 30 + 1];
		facial5points.push_back(Point2f(nose_x, nose_y));

		int lefttip_x = (int)p[6 + 2 * 48];
		int lefttip_y = (int)p[6 + 2 * 48 + 1];
		facial5points.push_back(Point2f(lefttip_x, lefttip_y));

		int righttip_x = (int)p[6 + 2 * 54];
		int righttip_y = (int)p[6 + 2 * 54 + 1];
		facial5points.push_back(Point2f(righttip_x, righttip_y));

		faces.push_back(std::make_pair(singlefaceloc, facial5points));
	}

	
	return faces;
}

FaceDetector::~FaceDetector(){

}
