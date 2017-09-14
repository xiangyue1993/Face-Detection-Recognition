#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parents) :QMainWindow(parents){
	ui.setupUi(this);

	connect(ui.LogWindowButton, SIGNAL(clicked()), this, SLOT(LogWindow_button_clicked()));
	connect(ui.RecognizerWindowButton, SIGNAL(clicked()), this, SLOT(RecognizerWindow_button_clicked()));
}

void MainWindow::LogWindow_button_clicked(){
	this->hide();
	logwindow_.show();
}

void MainWindow::RecognizerWindow_button_clicked(){
	this->hide();
	recognizerwindow_.show();
}

MainWindow::~MainWindow(){
}