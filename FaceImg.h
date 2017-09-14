#ifndef FACE_IMG
#define FACE_IMG
#include <opencv2\opencv.hpp>
#include <vector>
#include "FaceDetector.h"
#include "FeatureExtractor.h"

#define NO_FEATURE_EXTRACT 1

class FaceImg
{
public:
	cv::Mat srcImg;
	std::vector<SingleFaceInfo> multifaceinfo;
	std::vector<std::vector<float>> faceFeatures;

public:
	FaceImg();

public:
	void FaceProcess(cv::Mat& inputImage, int whether_extract_feature = 0);
	int MaxFaceIndex();

private:
	FaceDetector facedetector_;
	FeatureExtractor featureextractor_;
	std::vector<cv::Point2f> coord5points;
};

#endif