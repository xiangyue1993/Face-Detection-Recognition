#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "ui_MainWindow.h"
#include "RecognizerWindow.h"
#include "LogWindow.h"

#include <QtWidgets/QMainWindow>


class MainWindow: public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parents = 0);
	~MainWindow();

private:
	Ui::MainWindow ui;
	LogWindow logwindow_;
	RecognizerWindow recognizerwindow_;


private slots:
	void LogWindow_button_clicked();
	void RecognizerWindow_button_clicked();

};

#endif