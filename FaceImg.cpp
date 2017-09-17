#include "Headers/FaceImg.h"

FaceImg::FaceImg(){
	double dst_landmark[10] = {
		30.2946, 65.5318, 48.0252, 33.5493, 62.7299,
		51.6963, 51.5014, 71.7366, 92.3655, 92.2041 };

	for (int i = 0; i < 5; i++){
		coord5points.push_back(cv::Point2f(dst_landmark[i], dst_landmark[i + 5]));
	}
}

cv::Mat getsrc_roi(std::vector<cv::Point2f> x0, std::vector<cv::Point2f> dst)
{
	int size = dst.size();
	cv::Mat A = cv::Mat::zeros(size * 2, 4, CV_32FC1);
	cv::Mat B = cv::Mat::zeros(size * 2, 1, CV_32FC1);

	//[ x1 -y1 1 0] [a]       [x_1]
	//[ y1  x1 0 1] [b]   =   [y_1]
	//[ x2 -y2 1 0] [c]       [x_2]
	//[ y2  x2 0 1] [d]       [y_2]	

	for (int i = 0; i < size; i++)
	{
		A.at<float>(i << 1, 0) = x0[i].x;// roi_dst[i].x;
		A.at<float>(i << 1, 1) = -x0[i].y;
		A.at<float>(i << 1, 2) = 1;
		A.at<float>(i << 1, 3) = 0;
		A.at<float>(i << 1 | 1, 0) = x0[i].y;
		A.at<float>(i << 1 | 1, 1) = x0[i].x;
		A.at<float>(i << 1 | 1, 2) = 0;
		A.at<float>(i << 1 | 1, 3) = 1;

		B.at<float>(i << 1) = dst[i].x;
		B.at<float>(i << 1 | 1) = dst[i].y;
	}

	cv::Mat roi = cv::Mat::zeros(2, 3, A.type());
	cv::Mat AT = A.t();
	cv::Mat ATA = A.t() * A;
	cv::Mat R = ATA.inv() * AT * B;

	//roi = [a -b c;b a d ];

	roi.at<float>(0, 0) = R.at<float>(0, 0);
	roi.at<float>(0, 1) = -R.at<float>(1, 0);
	roi.at<float>(0, 2) = R.at<float>(2, 0);
	roi.at<float>(1, 0) = R.at<float>(1, 0);
	roi.at<float>(1, 1) = R.at<float>(0, 0);
	roi.at<float>(1, 2) = R.at<float>(3, 0);
	return roi;

}

void FaceImg::FaceProcess(cv::Mat& inputImage, int whether_extract_feature){
	faceFeatures.clear();
	srcImg = inputImage.clone();
	multifaceinfo = facedetector_.FaceDetection(srcImg);

	if (whether_extract_feature == 0){
		for (int i = 0; i < multifaceinfo.size(); i++){
			cv::Mat warp_mat, cropImg;

			warp_mat = cv::estimateRigidTransform(multifaceinfo[i].second, coord5points, false);
			if (warp_mat.empty()){
				warp_mat = getsrc_roi(multifaceinfo[i].second, coord5points);
			}
			warp_mat.convertTo(warp_mat, CV_32FC1);
			cropImg = cv::Mat::zeros(INPUTIMAGE_HEIGHT, INPUTIMAGE_WIDTH, srcImg.type());
			warpAffine(srcImg, cropImg, warp_mat, cropImg.size());
			cropImg.convertTo(cropImg, CV_32FC1);

			faceFeatures.push_back(featureextractor_.ExtractFeature(cropImg));
		}
	}
}

int FaceImg::MaxFaceIndex(){
	int maxFaceSize = multifaceinfo[0].first.width * multifaceinfo[0].first.height;
	int maxIndex = 0;

	for (int i = 1; i < multifaceinfo.size(); i++){
		if (multifaceinfo[i].first.width * multifaceinfo[i].first.height > maxFaceSize){
			maxFaceSize = multifaceinfo[i].first.width * multifaceinfo[i].first.height;
			maxIndex = i;
		}
	}

	return maxIndex;
}
