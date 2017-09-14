#include "RecognizerWindow.h"

RecognizerWindow::RecognizerWindow(QWidget* parent) :QMainWindow(parent){
	ui.setupUi(this);
	ui.DisplayLabel->setScaledContents(true);

	faceimg_ = new FaceImg();
	distancecalculator_ = new DistanceCalculator();
	cam_ = new Camera();
	timer_1 = new QTimer();
	timer_2 = new QTimer();
	video_ = new VideoCapture();

	connect(ui.CameraButton, SIGNAL(clicked()), this, SLOT(on_camerabutton_clicked()));
	connect(timer_1, SIGNAL(timeout()), this, SLOT(display_camera()));
	connect(ui.PictureButton, SIGNAL(clicked()), this, SLOT(on_picturebutton_clicked()));
	connect(ui.VideoButton, SIGNAL(clicked()), this, SLOT(on_videobutton_clicked()));
	connect(timer_2, SIGNAL(timeout()), this, SLOT(display_video()));
}

void RecognizerWindow::on_picturebutton_clicked(){
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"),
		".", tr("Image Files (*.png *.jpg *.bmp)"));
	qDebug() << "filenames:" << fileName;

	Picture = cv::imread(fileName.toStdString());
	if (!Picture.empty()){
		if (cam_->IsCameraOpen()){
			cam_->CloseCamera();
			timer_1->stop();
		}
		if (video_->isOpened()){
			video_->release();
			timer_2->stop();
		}
		FaceImg faceprocessor_;
		std::string Name;

		faceprocessor_.FaceProcess(Picture);
		for (int i = 0; i < faceprocessor_.faceFeatures.size(); i++){
			Name = distancecalculator_->MostLikeFace(faceprocessor_.faceFeatures[i]);
			cv::rectangle(Picture, faceprocessor_.multifaceinfo[i].first, cv::Scalar(0, 0, 255), 2);
			putTextZH(Picture, Name.c_str(), cv::Point(faceprocessor_.multifaceinfo[i].first.x, faceprocessor_.multifaceinfo[i].first.y + faceprocessor_.multifaceinfo[i].first.height - faceprocessor_.multifaceinfo[i].first.height / 6),
				cv::Scalar(0, 255, 0), faceprocessor_.multifaceinfo[i].first.height / 6, "ºÚÌå");
			//cv::putText(Picture, Name, cv::Point(faceprocessor_.faceLocations[i].x, faceprocessor_.faceLocations[i].y + faceprocessor_.faceLocations[i].height),
			//	FONT_HERSHEY_COMPLEX, 1.5, cv::Scalar(0, 255, 0), 4);
		}
		ui.DisplayLabel->setPixmap(QPixmap::fromImage(Mat2QImage(Picture)));
	}
}

void RecognizerWindow::on_camerabutton_clicked(){
	if (video_->isOpened()){
		timer_2->stop();
		video_->release();
	}
	cam_->OpenCamera();
	timer_1->start(33);
}

void RecognizerWindow::display_camera(){
	cv::Mat frame;
	std::string Name;

	frame = cam_->ReadCamera();
	faceimg_->FaceProcess(frame);
	for (int i = 0; i < faceimg_->faceFeatures.size(); i++){
		cv::Rect faceLocations(faceimg_->multifaceinfo[i].first);

		Name = distancecalculator_->MostLikeFace(faceimg_->faceFeatures[i]);
		cv::rectangle(frame, faceLocations, cv::Scalar(0, 0, 255), 2);

		putTextZH(frame, Name.c_str(), cv::Point(faceLocations.x, faceLocations.y + faceLocations.height - faceLocations.height / 6),
			cv::Scalar(0, 255, 0), faceLocations.height / 6, "ºÚÌå");

		/*cv::putText(frame, Name, cv::Point(faceLocations.x, faceLocations.y + faceLocations.height),
			FONT_HERSHEY_COMPLEX, 1.5, cv::Scalar(0, 255, 0), 4);*/
	}
	ui.DisplayLabel->setPixmap(QPixmap::fromImage(Mat2QImage(frame)));
}

void RecognizerWindow::on_videobutton_clicked(){
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"),
		".", tr("Video Files (*.mp4 *.rmvb *.avi *.wmv)"));
	qDebug() << "filenames:" << fileName;

	video_->open(fileName.toStdString());
	if (video_->isOpened()){
		if (cam_->IsCameraOpen()){
			cam_->CloseCamera();
			timer_1->stop();
		}
		timer_2->start(33);
	}
}

void RecognizerWindow::display_video(){
	cv::Mat frame;
	std::string Name;

	double rate = video_->get(CV_CAP_PROP_FPS);

	if (video_->read(frame)){
		faceimg_->FaceProcess(frame);
		for (int i = 0; i < faceimg_->faceFeatures.size(); i++){
			cv::Rect faceLocations(faceimg_->multifaceinfo[i].first);

			Name = distancecalculator_->MostLikeFace(faceimg_->faceFeatures[i]);
			cv::rectangle(frame, faceLocations, cv::Scalar(0, 0, 255), 2);
			putTextZH(frame, Name.c_str(), cv::Point(faceLocations.x, faceLocations.y + faceLocations.height - faceLocations.height / 6),
				cv::Scalar(0, 255, 0), faceLocations.height / 6, "ºÚÌå");
			/*cv::putText(frame, Name, cv::Point(faceLocations.x, faceLocations.y + faceLocations.height),
				FONT_HERSHEY_COMPLEX, 1.5, cv::Scalar(0, 255, 0), 4);*/
		}
		ui.DisplayLabel->setPixmap(QPixmap::fromImage(Mat2QImage(frame)));
	}
	else{
		video_->release();
		timer_1->stop();
	}

	
}


QImage RecognizerWindow::Mat2QImage(Mat& Img){
	QImage qImg;

	if (Img.channels() == 3)                             //3 channels color image
	{

		cv::cvtColor(Img, Img, CV_BGR2RGB);
		qImg = QImage((const unsigned char*)(Img.data),
			Img.cols, Img.rows,
			Img.cols * Img.channels(),
			QImage::Format_RGB888);
	}
	else if (Img.channels() == 1)                    //grayscale image
	{
		qImg = QImage((const unsigned char*)(Img.data),
			Img.cols, Img.rows,
			Img.cols * Img.channels(),
			QImage::Format_Indexed8);
	}
	else
	{
		qImg = QImage((const unsigned char*)(Img.data),
			Img.cols, Img.rows,
			Img.cols * Img.channels(),
			QImage::Format_RGB888);
	}

	return qImg;
}

RecognizerWindow::~RecognizerWindow(){

}