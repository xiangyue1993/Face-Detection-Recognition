#ifndef FEATURE_EXTRACTOR
#define FEATURE_EXTRACTOR

#include "opencv2\opencv.hpp"

#include <cstring>
#include <iostream>
#include <cstdlib>
#include <vector>

#define INPUTIMAGE_WIDTH 96
#define INPUTIMAGE_HEIGHT 112
#define OUTPUT_VECTOR_SIZE 512
#define MaxThread 8

class FeatureExtractor
{
public:
	FeatureExtractor();

private:
	std::string ModelFileName;
	std::string TrainedFileName;

public:
	static std::vector<float> ExtractFeature(cv::Mat& srcImg, int threadID = 0);
	std::vector<std::vector<float>> ExtractFeature(std::vector<cv::Mat>& srcImg);

};

#endif
