/********************************************************************************
** Form generated from reading UI file 'LogWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGWINDOW_H
#define UI_LOGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogWindow
{
public:
    QWidget *centralWidget;
    QPushButton *CameraOpenButton;
    QPushButton *CameraCloseButton;
    QLabel *DisplayLabel;
    QPushButton *PhotoButton;
    QLabel *NameLabel;
    QLabel *PictureLabel;
    QPushButton *SaveButton;
    QLineEdit *NameInputText;
    QPushButton *LoadFileButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LogWindow)
    {
        if (LogWindow->objectName().isEmpty())
            LogWindow->setObjectName(QStringLiteral("LogWindow"));
        LogWindow->resize(1207, 609);
        centralWidget = new QWidget(LogWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CameraOpenButton = new QPushButton(centralWidget);
        CameraOpenButton->setObjectName(QStringLiteral("CameraOpenButton"));
        CameraOpenButton->setGeometry(QRect(50, 480, 101, 41));
        CameraCloseButton = new QPushButton(centralWidget);
        CameraCloseButton->setObjectName(QStringLiteral("CameraCloseButton"));
        CameraCloseButton->setGeometry(QRect(360, 480, 111, 41));
        DisplayLabel = new QLabel(centralWidget);
        DisplayLabel->setObjectName(QStringLiteral("DisplayLabel"));
        DisplayLabel->setGeometry(QRect(20, 10, 491, 421));
        DisplayLabel->setFrameShape(QFrame::NoFrame);
        DisplayLabel->setFrameShadow(QFrame::Plain);
        PhotoButton = new QPushButton(centralWidget);
        PhotoButton->setObjectName(QStringLiteral("PhotoButton"));
        PhotoButton->setGeometry(QRect(210, 480, 91, 41));
        NameLabel = new QLabel(centralWidget);
        NameLabel->setObjectName(QStringLiteral("NameLabel"));
        NameLabel->setGeometry(QRect(670, 60, 81, 41));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        NameLabel->setFont(font);
        PictureLabel = new QLabel(centralWidget);
        PictureLabel->setObjectName(QStringLiteral("PictureLabel"));
        PictureLabel->setGeometry(QRect(750, 150, 301, 271));
        SaveButton = new QPushButton(centralWidget);
        SaveButton->setObjectName(QStringLiteral("SaveButton"));
        SaveButton->setGeometry(QRect(820, 480, 141, 41));
        NameInputText = new QLineEdit(centralWidget);
        NameInputText->setObjectName(QStringLiteral("NameInputText"));
        NameInputText->setGeometry(QRect(740, 50, 301, 61));
        LoadFileButton = new QPushButton(centralWidget);
        LoadFileButton->setObjectName(QStringLiteral("LoadFileButton"));
        LoadFileButton->setGeometry(QRect(960, 440, 93, 28));
        LogWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LogWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1207, 26));
        LogWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LogWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LogWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LogWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LogWindow->setStatusBar(statusBar);

        retranslateUi(LogWindow);

        QMetaObject::connectSlotsByName(LogWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LogWindow)
    {
        LogWindow->setWindowTitle(QApplication::translate("LogWindow", "LogWindow", Q_NULLPTR));
        CameraOpenButton->setText(QApplication::translate("LogWindow", "OpenCamera", Q_NULLPTR));
        CameraCloseButton->setText(QApplication::translate("LogWindow", "CloseCamera", Q_NULLPTR));
        DisplayLabel->setText(QApplication::translate("LogWindow", "CameraDisplay", Q_NULLPTR));
        PhotoButton->setText(QApplication::translate("LogWindow", "Photograph", Q_NULLPTR));
        NameLabel->setText(QApplication::translate("LogWindow", "Name", Q_NULLPTR));
        PictureLabel->setText(QApplication::translate("LogWindow", "PictureDisplay", Q_NULLPTR));
        SaveButton->setText(QApplication::translate("LogWindow", "SaveFaceFeature", Q_NULLPTR));
        LoadFileButton->setText(QApplication::translate("LogWindow", "Load Image", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LogWindow: public Ui_LogWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGWINDOW_H
