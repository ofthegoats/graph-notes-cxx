/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QListView *listView;
    QPushButton *setGreenButton;
    QPushButton *setRedButton;
    QPushButton *newNoteButton;
    QPushButton *setBlueButton;
    QTabWidget *tabWidget;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1024, 770);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setMaximumSize(QSize(276, 16777215));

        gridLayout->addWidget(listView, 2, 0, 1, 1);

        setGreenButton = new QPushButton(centralwidget);
        setGreenButton->setObjectName(QString::fromUtf8("setGreenButton"));

        gridLayout->addWidget(setGreenButton, 0, 2, 1, 1);

        setRedButton = new QPushButton(centralwidget);
        setRedButton->setObjectName(QString::fromUtf8("setRedButton"));

        gridLayout->addWidget(setRedButton, 0, 1, 1, 1);

        newNoteButton = new QPushButton(centralwidget);
        newNoteButton->setObjectName(QString::fromUtf8("newNoteButton"));
        newNoteButton->setMaximumSize(QSize(413, 16777215));

        gridLayout->addWidget(newNoteButton, 0, 0, 1, 1);

        setBlueButton = new QPushButton(centralwidget);
        setBlueButton->setObjectName(QString::fromUtf8("setBlueButton"));

        gridLayout->addWidget(setBlueButton, 0, 3, 1, 1);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));

        gridLayout->addWidget(tabWidget, 2, 1, 1, 3);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        setGreenButton->setText(QCoreApplication::translate("MainWindow", "green", nullptr));
        setRedButton->setText(QCoreApplication::translate("MainWindow", "red", nullptr));
        newNoteButton->setText(QCoreApplication::translate("MainWindow", "new", nullptr));
        setBlueButton->setText(QCoreApplication::translate("MainWindow", "blue", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_H
