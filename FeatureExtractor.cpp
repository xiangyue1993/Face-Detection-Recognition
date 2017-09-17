#include "FeatureExtractor.h"

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

caffe::Net<float>* net_;
caffe::MemoryDataLayer<float>* memory_layer;


FeatureExtractor::FeatureExtractor(){
	ModelFileName = "Resources\\face_deploy.prototxt";
	TrainedFileName = "Resources\\umd1face1.caffemodel";

	net_ = new caffe::Net<float>(ModelFileName, caffe::TEST);
	net_->CopyTrainedLayersFrom(TrainedFileName);
	memory_layer = (caffe::MemoryDataLayer<float> *)net_->layers()[0].get();
}

std::vector<float> FeatureExtractor::ExtractFeature(cv::Mat& srcImg){
#ifdef CPU_ONLY
	caffe::Caffe::set_mode(caffe::Caffe::CPU);
#else
	caffe::Caffe::set_mode(caffe::Caffe::GPU);
#endif

	std::vector<cv::Mat> InputImg;
	std::vector<int> tempLabel;
	std::vector<float> features;

	srcImg.convertTo(srcImg, CV_8U);

	InputImg.push_back(srcImg.clone());
	tempLabel.push_back(0);

	cv::flip(srcImg, srcImg, 1);	//flip

	InputImg.push_back(srcImg.clone());
	tempLabel.push_back(0);

	memory_layer->AddMatVector(InputImg, tempLabel);
	std::vector<caffe::Blob<float>*> input_vec;
	net_->Forward(input_vec);

	boost::shared_ptr<caffe::Blob<float>> fc5 = net_->blob_by_name("fc5");

	for (int i = 0; i < 2; i++){//index of image
		for (int j = 0; j < OUTPUT_VECTOR_SIZE; j++){
			features.push_back(fc5->data_at(i, j, 0, 0));
		}
	}
	
	return features;
}


