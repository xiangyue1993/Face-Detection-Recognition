#ifndef PUTTEXT_H_
#define PUTTEXT_H_

#include <string>
#include <opencv2/opencv.hpp>

//using namespace cv;

//The function putTextZH() is used to display Chinese on image, English also supported
void putTextZH(cv::Mat &dst, const char* str, cv::Point org, cv::Scalar color, int fontSize,
	const char *fn = "Arial", bool italic = false, bool underline = false);

#endif // PUTTEXT_H_