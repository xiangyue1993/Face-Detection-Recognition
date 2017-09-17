#include "Headers/LogWindow.h"
#include "qmessagebox.h"

LogWindow::LogWindow(QWidget* parent) :QMainWindow(parent){

	ui.setupUi(this);
	ui.DisplayLabel->setScaledContents(true);
	ui.PictureLabel->setScaledContents(true);
	ui.SaveButton->setEnabled(false);

	camera = new Camera();
	faceimg_ = new FaceImg();

	timer = new QTimer();
	IsPictureShowed = false;

	connect(ui.CameraOpenButton, SIGNAL(clicked()), this, SLOT(CameraOpen()));
	connect(timer, SIGNAL(timeout()), this, SLOT(Display()));
	connect(ui.PhotoButton, SIGNAL(clicked()), this, SLOT(ShowPicture()));
	connect(ui.CameraCloseButton, SIGNAL(clicked()), this, SLOT(CameraClose()));
	connect(ui.NameInputText, SIGNAL(textChanged(const QString &)), this, SLOT(SaveButtonChange(const QString &)));
	connect(ui.SaveButton, SIGNAL(clicked()), this, SLOT(WriteToDatabase()));
	connect(ui.LoadFileButton, SIGNAL(clicked()), this, SLOT(LoadFileButtonClicked()));
}

//Read frame from camera and detect the face in real time
void LogWindow::Display(){
	cv::Mat frame;

	//Read frame from camera
	frame = camera->ReadCamera();
	//Face detection
	faceimg_->FaceProcess(frame, NO_FEATURE_EXTRACT);

	for (int i = 0; i < faceimg_->multifaceinfo.size(); i++){
		//Draw out the face region
		cv::rectangle(frame, faceimg_->multifaceinfo[i].first, cv::Scalar(0, 0, 255), 2);
	}

	//Display
	ui.DisplayLabel->setPixmap(QPixmap::fromImage(Mat2QImage(frame)));
}

void LogWindow::ShowPicture(){
	if (camera->IsCameraOpen() && !faceimg_->srcImg.empty()){
		Picture= faceimg_->srcImg.clone();
		ui.PictureLabel->setPixmap(QPixmap::fromImage(Mat2QImage(Picture)));

		IsPictureShowed = true;

		if (!ui.NameInputText->text().isEmpty()){
			ui.SaveButton->setEnabled(true);
		}
	}
}

void LogWindow::CameraOpen(){
	camera->OpenCamera();
	timer->start(33);
}

void LogWindow::CameraClose(){
	camera->CloseCamera();
	timer->stop();
	ui.DisplayLabel->clear();
}

//Save the feature extracted in a .dat file
void LogWindow::WriteToDatabase(){
	std::ofstream fout("OutputFeature\\features.dat", std::ios::app);

	FaceImg outputImage;
	std::string outputLabel;

	//Detect face in picture
	outputImage.FaceProcess(Picture);
	
	outputLabel = ui.NameInputText->text().toStdString();

	if (outputImage.faceFeatures.size() > 0){
		fout << outputLabel << std::endl;

		//Only save the feature of the max face in picture
		int maxFaceIndex = outputImage.MaxFaceIndex();

		for (int i = 0; i < outputImage.faceFeatures[maxFaceIndex].size(); i++){
			i == 0 ? (fout << outputImage.faceFeatures[maxFaceIndex][i]) :
				(fout << " " << outputImage.faceFeatures[maxFaceIndex][i]);
		}
		fout << std::endl;
		QMessageBox::about(NULL, "OK", "The features has been saved successfully!");
	}
	else{
		QMessageBox::about(NULL, "Error", "No face detected! Please load an another picture.");
	}
	ui.NameInputText->clear();
	ui.PictureLabel->clear();
	IsPictureShowed = false;

	fout << std::flush;
	fout.close();
}

//Load image file
void LogWindow::LoadFileButtonClicked(){
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"),
									".", tr("Image Files (*.png *.jpg *.bmp)"));
	qDebug() << "filenames:" << fileName;

	Picture = cv::imread(fileName.toStdString());
	if (!Picture.empty()){
		ui.PictureLabel->setPixmap(QPixmap::fromImage(Mat2QImage(Picture)));
		IsPictureShowed = true;
		if (!ui.NameInputText->text().isEmpty()){
			ui.SaveButton->setEnabled(true);
		}
	}
}

//Convert Mat to QImage
QImage LogWindow::Mat2QImage(Mat& Img){
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

void LogWindow::SaveButtonChange(const QString& NameText){
	if (IsPictureShowed && !NameText.isEmpty()){
		ui.SaveButton->setEnabled(true);
	}
	else
		ui.SaveButton->setEnabled(false);
}

LogWindow::~LogWindow(){

}
