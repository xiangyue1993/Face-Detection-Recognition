#ifndef DISTANCE_CALCULATOR
#define DISTANCE_CALCULATOR

#include <vector>

class DistanceCalculator
{
public:
	std::vector<std::vector<float>> HistoryFaceFeatures;
	std::vector<std::string> HistoryFaceLabels;

public:
	DistanceCalculator();

public:
	std::string MostLikeFace(std::vector<float> TestFaceFeature);

};

#endif
