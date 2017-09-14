#ifndef FACE_DETECTOR
#define FACE_DETECTOR

#include "opencv2/core/core.hpp"     
#include "opencv2/objdetect/objdetect.hpp"     
#include "opencv2/highgui/highgui.hpp"     
#include "opencv2/imgproc/imgproc.hpp" 

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

typedef std::pair<cv::Rect, std::vector<cv::Point2f>> SingleFaceInfo;

class FaceDetector
{
public:
	~FaceDetector();

public:
	std::vector<SingleFaceInfo> FaceDetection(cv::Mat& srcImg);
};

#endif