/********************************************************************************
** Form generated from reading UI file 'RecognizerWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECOGNIZERWINDOW_H
#define UI_RECOGNIZERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecognizerWindow
{
public:
    QWidget *centralwidget;
    QLabel *DisplayLabel;
    QPushButton *PictureButton;
    QPushButton *CameraButton;
    QPushButton *VideoButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *RecognizerWindow)
    {
        if (RecognizerWindow->objectName().isEmpty())
            RecognizerWindow->setObjectName(QStringLiteral("RecognizerWindow"));
        RecognizerWindow->resize(1128, 729);
        centralwidget = new QWidget(RecognizerWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        DisplayLabel = new QLabel(centralwidget);
        DisplayLabel->setObjectName(QStringLiteral("DisplayLabel"));
        DisplayLabel->setGeometry(QRect(40, 40, 771, 481));
        PictureButton = new QPushButton(centralwidget);
        PictureButton->setObjectName(QStringLiteral("PictureButton"));
        PictureButton->setGeometry(QRect(910, 30, 131, 51));
        CameraButton = new QPushButton(centralwidget);
        CameraButton->setObjectName(QStringLiteral("CameraButton"));
        CameraButton->setGeometry(QRect(910, 190, 131, 51));
        VideoButton = new QPushButton(centralwidget);
        VideoButton->setObjectName(QStringLiteral("VideoButton"));
        VideoButton->setGeometry(QRect(910, 110, 131, 51));
        RecognizerWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RecognizerWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1128, 26));
        RecognizerWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(RecognizerWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        RecognizerWindow->setStatusBar(statusbar);

        retranslateUi(RecognizerWindow);

        QMetaObject::connectSlotsByName(RecognizerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RecognizerWindow)
    {
        RecognizerWindow->setWindowTitle(QApplication::translate("RecognizerWindow", "Recognizer", Q_NULLPTR));
        DisplayLabel->setText(QString());
        PictureButton->setText(QApplication::translate("RecognizerWindow", "Load Image", Q_NULLPTR));
        CameraButton->setText(QApplication::translate("RecognizerWindow", "From Camera", Q_NULLPTR));
        VideoButton->setText(QApplication::translate("RecognizerWindow", "Load Video", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RecognizerWindow: public Ui_RecognizerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECOGNIZERWINDOW_H
