#ifndef CLASSIFY_WINDOW
#define CLASSIFY_WINDOW

#include "ui_RecognizerWindow.h"
#include "FaceImg.h"
#include "DistanceCalculator.h"
#include "Camera.h"
#include "PutText.h"

#include <QtWidgets/QMainWindow>
#include <QtCore\qtimer.h>
#include <qfiledialog.h>
#include <qdebug.h>


class RecognizerWindow : public QMainWindow
{
	Q_OBJECT

public:
	RecognizerWindow(QWidget* parent = 0);
	~RecognizerWindow();
private:
	Ui::RecognizerWindow ui;
	FaceImg* faceimg_;
	DistanceCalculator* distancecalculator_;
	Camera* cam_;
	VideoCapture* video_;
	QTimer *timer_1, *timer_2;
	cv::Mat Picture;

private slots:
	void on_picturebutton_clicked();
	void on_camerabutton_clicked();
	void display_camera();
	void on_videobutton_clicked();
	void display_video();

private:
	QImage Mat2QImage(cv::Mat& srcImg);
};

#endif