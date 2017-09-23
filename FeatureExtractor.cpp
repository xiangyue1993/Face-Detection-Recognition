#include "Headers/FeatureExtractor.h"

#include "caffe/layers/input_layer.hpp"  
#include "caffe/layers/inner_product_layer.hpp"  
#include "caffe/layers/dropout_layer.hpp"  
#include "caffe/layers/conv_layer.hpp"  
#include "caffe/layers/relu_layer.hpp"  
#include <iostream> 
#include "caffe/caffe.hpp"
#include "opencv2/opencv.hpp"
#include <caffe/layers/memory_data_layer.hpp>
#include "caffe/layers/pooling_layer.hpp"  
#include "caffe/layers/lrn_layer.hpp"  
#include "caffe/layers/softmax_layer.hpp"

#include <Windows.h>

caffe::Net<float>* net_[MaxThread];
caffe::MemoryDataLayer<float>* memory_layer[MaxThread];
std::vector<std::vector<float>> features;
std::vector<int> seq;
bool isAvailable[MaxThread];
static bool IsNetInitialized = false;
HANDLE hMutex = CreateMutex(NULL, FALSE, NULL);

struct threadArgument{
	cv::Mat singleface;
	int index;
	threadArgument(){}
	threadArgument(cv::Mat img, int t) :singleface(img.clone()), index(t){}
};


FeatureExtractor::FeatureExtractor(){
	ModelFileName = "Resources\\face_deploy.prototxt";
	TrainedFileName = "Resources\\umd1face1.caffemodel";
	
	if (!IsNetInitialized){
		for (int i = 0; i < MaxThread; i++){
			net_[i] = new caffe::Net<float>(ModelFileName, caffe::TEST);
			net_[i]->CopyTrainedLayersFrom(TrainedFileName);
			memory_layer[i] = (caffe::MemoryDataLayer<float> *)net_[i]->layers()[0].get();
			isAvailable[i] = true;
		}
		IsNetInitialized = true;
	}
}

std::vector<float> FeatureExtractor::ExtractFeature(cv::Mat& srcImg, int threadID){
#ifdef CPU_ONLY
	caffe::Caffe::set_mode(caffe::Caffe::CPU);
#else
	caffe::Caffe::set_mode(caffe::Caffe::GPU);
#endif

	if (threadID >= MaxThread) threadID = threadID % MaxThread;

	std::vector<cv::Mat> InputImg;
	std::vector<int> tempLabel;
	std::vector<float> singlefeatures;

	srcImg.convertTo(srcImg, CV_8U);

	InputImg.push_back(srcImg.clone());
	tempLabel.push_back(0);

	cv::flip(srcImg, srcImg, 1);	//flip

	InputImg.push_back(srcImg.clone());
	tempLabel.push_back(0);

	memory_layer[threadID]->AddMatVector(InputImg, tempLabel);
	std::vector<caffe::Blob<float>*> input_vec;
	net_[threadID]->Forward(input_vec);

	boost::shared_ptr<caffe::Blob<float>> fc5 = net_[threadID]->blob_by_name("fc5");

	for (int i = 0; i < 2; i++){//index of image
		for (int j = 0; j < OUTPUT_VECTOR_SIZE; j++){
			singlefeatures.push_back(fc5->data_at(i, j, 0, 0));
		}
	}
	
	return singlefeatures;
}

void threadDistribution(threadArgument* args){
	std::vector<float> singlefeatures;

	while (1){
		WaitForSingleObject(hMutex, INFINITE);
		if (isAvailable[args->index % MaxThread]){
			isAvailable[args->index % MaxThread] = false;
			ReleaseMutex(hMutex);
			break;
		}
		ReleaseMutex(hMutex);
	}

	singlefeatures = FeatureExtractor::ExtractFeature(args->singleface, args->index);

	WaitForSingleObject(hMutex, INFINITE);
	features.push_back(singlefeatures);
	seq.push_back(args->index);
	isAvailable[args->index % MaxThread] = true;
	ReleaseMutex(hMutex);
}


std::vector<std::vector<float>> FeatureExtractor::ExtractFeature(std::vector<cv::Mat>& srcImg){
	features.clear();
	seq.clear();

	std::vector<std::vector<float>> result;
	int facenum = srcImg.size();
	HANDLE* _thread = new HANDLE[facenum];
	threadArgument* args = new threadArgument[facenum];

	for (int i = 0; i < facenum; i++){
		args[i].singleface = srcImg[i].clone();
		args[i].index = i;
	}

	for (int i = 0; i < facenum; i++){
		_thread[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)threadDistribution, &args[i], 1, NULL);
	}

	WaitForMultipleObjects(facenum, _thread, TRUE, INFINITE);

	for (int i = 0; i < facenum; i++){
		CloseHandle(_thread[i]);
	}

	for (int i = 0; i < facenum; i++){
		for (int j = 0; j < facenum; j++){
			if (i == seq[j]){
				result.push_back(features[j]);
				break;
			}
		}
	}

	return result;
}
