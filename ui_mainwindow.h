/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *frameLabel;
    QPushButton *pushButton_set_region;
    QPushButton *pushButton_reset_region;
    QPushButton *pushButton_startrecord;
    QPushButton *pushButton_stoprecord;
    QCheckBox *checkBox;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(700, 650);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(440, 80));
        MainWindow->setMaximumSize(QSize(700, 650));
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        frameLabel = new QLabel(centralWidget);
        frameLabel->setObjectName(QStringLiteral("frameLabel"));
        frameLabel->setGeometry(QRect(20, 90, 640, 480));
        frameLabel->setMinimumSize(QSize(100, 200));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font.setPointSize(26);
        font.setBold(true);
        font.setWeight(75);
        frameLabel->setFont(font);
        frameLabel->setCursor(QCursor(Qt::CrossCursor));
        frameLabel->setFrameShape(QFrame::Panel);
        frameLabel->setLineWidth(3);
        frameLabel->setMidLineWidth(5);
        frameLabel->setAlignment(Qt::AlignCenter);
        frameLabel->setIndent(-1);
        pushButton_set_region = new QPushButton(centralWidget);
        pushButton_set_region->setObjectName(QStringLiteral("pushButton_set_region"));
        pushButton_set_region->setGeometry(QRect(20, 30, 75, 23));
        QFont font1;
        font1.setFamily(QStringLiteral("Times New Roman"));
        pushButton_set_region->setFont(font1);
        pushButton_reset_region = new QPushButton(centralWidget);
        pushButton_reset_region->setObjectName(QStringLiteral("pushButton_reset_region"));
        pushButton_reset_region->setGeometry(QRect(110, 30, 75, 23));
        pushButton_reset_region->setFont(font1);
        pushButton_startrecord = new QPushButton(centralWidget);
        pushButton_startrecord->setObjectName(QStringLiteral("pushButton_startrecord"));
        pushButton_startrecord->setGeometry(QRect(210, 10, 51, 51));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\273\237\346\255\243\351\273\221\351\253\224"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        pushButton_startrecord->setFont(font2);
        pushButton_startrecord->setFocusPolicy(Qt::StrongFocus);
        pushButton_startrecord->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/background_img/background/strat.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_startrecord->setIcon(icon);
        pushButton_startrecord->setIconSize(QSize(40, 40));
        pushButton_startrecord->setFlat(true);
        pushButton_stoprecord = new QPushButton(centralWidget);
        pushButton_stoprecord->setObjectName(QStringLiteral("pushButton_stoprecord"));
        pushButton_stoprecord->setGeometry(QRect(270, 8, 61, 52));
        pushButton_stoprecord->setStyleSheet(QLatin1String("color: rgb(85, 41, 27);\n"
"background-color: rgb(255, 255, 127);"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/background_img/background/stop_icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_stoprecord->setIcon(icon1);
        pushButton_stoprecord->setIconSize(QSize(65, 65));
        pushButton_stoprecord->setFlat(true);
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(350, 30, 73, 16));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        pushButton_startrecord->setDefault(true);
        pushButton_stoprecord->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Class support system", 0));
        frameLabel->setText(QApplication::translate("MainWindow", "\350\253\213\345\205\210\351\273\236\346\255\244\347\231\273\345\205\245", 0));
        pushButton_set_region->setText(QApplication::translate("MainWindow", "Set region", 0));
        pushButton_reset_region->setText(QApplication::translate("MainWindow", "Reset region", 0));
        pushButton_startrecord->setText(QString());
        pushButton_stoprecord->setText(QString());
        checkBox->setText(QApplication::translate("MainWindow", "Show", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
