#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_LogWindow.h"
#include "Camera.h"
#include "FaceImg.h"

#include <fstream>

#include <QtWidgets/QMainWindow>
#include <QtCore\qtimer.h>
#include <qfiledialog.h>
#include <qdebug.h>

class LogWindow : public QMainWindow
{
	Q_OBJECT

public:
	LogWindow(QWidget* parents = 0);
	~LogWindow();

private:
	Ui::LogWindow ui;
	Camera* camera;
	FaceImg* faceimg_;
	QTimer *timer;
	cv::Mat Picture;

private:
	bool IsPictureShowed;

private slots:
    void CameraOpen();
	void Display();
	void CameraClose();
	void ShowPicture();
	void WriteToDatabase();
	void SaveButtonChange(const QString& NameText);
	void LoadFileButtonClicked();

private:
	QImage Mat2QImage(Mat& Img);

};

#endif