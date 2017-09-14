#include "DistanceCalculator.h"
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <strstream>  

void UnicodeToAnsi(wchar_t* wszString, std::string& Res){
	int ansiLen = ::WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), NULL, 0, NULL, NULL);
	char* szAnsi = new char[ansiLen + 1];
	::WideCharToMultiByte(CP_ACP, NULL, wszString, wcslen(wszString), szAnsi, ansiLen, NULL, NULL);
	szAnsi[ansiLen] = '\0';

	Res = szAnsi;
}

std::string Utf8ToAnsi(std::string srcString){
	std::string Res;

	char* szU8 = new char[srcString.size()];
	strcpy(szU8, srcString.c_str());

	//Utf8ToUnicode
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), NULL, 0);
	wchar_t* wszString = new wchar_t[wcsLen + 1];
	::MultiByteToWideChar(CP_UTF8, NULL, szU8, strlen(szU8), wszString, wcsLen);
	wszString[wcsLen] = '\0';

	//UnicodeToUAnsi
	UnicodeToAnsi(wszString, Res);

	return Res;
}

DistanceCalculator::DistanceCalculator(){
	std::ifstream finput("OutputFeature\\features.dat");
	std::streambuf* old_buffer = std::cin.rdbuf(finput.rdbuf());

	std::string buffer;
	std::vector<float> SingleFeature;
	std::string singleLabel;

	while (std::getline(finput, buffer)){
		singleLabel = Utf8ToAnsi(buffer);	//If the features.dat file is encoded with utf8 then this line is required
		HistoryFaceLabels.push_back(singleLabel);
		getline(finput, buffer);
		std::istringstream stream(buffer);
		float temp;
		while (stream >> temp){
			SingleFeature.push_back(temp);
		}
		HistoryFaceFeatures.push_back(SingleFeature);
		SingleFeature.clear();
	}

	std::cin.rdbuf(old_buffer);
}

//Cosine value is used to determine the most similar face
std::string DistanceCalculator::MostLikeFace(std::vector<float> TestFaceFeature){
	std::string RecognizationResult = "UnKnown";
	int ResIndex = -1;
	float MaxCosine = 0;;

	for (int i = 0; i < HistoryFaceFeatures.size(); i++){
		float FeatureLen_1 = 0, FeatureLen_2 = 0, InnerProduct = 0;
		for (int j = 0; j < HistoryFaceFeatures[i].size(); j++){
			FeatureLen_1 += (TestFaceFeature[j] * TestFaceFeature[j]);
			FeatureLen_2 += (HistoryFaceFeatures[i][j] * HistoryFaceFeatures[i][j]);
			InnerProduct += (TestFaceFeature[j] * HistoryFaceFeatures[i][j]);
		}
		float Cosine;
		Cosine = InnerProduct / (sqrt(FeatureLen_1) * sqrt(FeatureLen_2));

		if (Cosine>MaxCosine){
			MaxCosine = Cosine;
			ResIndex = i;
		}
	}

	if (MaxCosine > 0.7){
		char str_similarity[10];

		int Similarity = MaxCosine * 100;
		itoa(Similarity, str_similarity, 10);

		RecognizationResult = HistoryFaceLabels[ResIndex] + " " + str_similarity + "%";
	}


	return RecognizationResult;
}