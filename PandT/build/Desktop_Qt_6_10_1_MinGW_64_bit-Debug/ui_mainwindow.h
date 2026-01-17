/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *selectBTN;
    QPushButton *unzipBTN;
    QPushButton *deleteBTN;
    QPushButton *imgZipBTN;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *backBTN;
    QPushButton *forwardBTN;
    QPushButton *refreshBTN;
    QPushButton *upBTN;
    QLineEdit *pathEdit;
    QLabel *label;
    QLineEdit *filterEdit;
    QTableView *fileTable;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(820, 470);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(820, 470));
        MainWindow->setMaximumSize(QSize(820, 470));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 20, 781, 411));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, -1, 0, -1);
        selectBTN = new QPushButton(layoutWidget);
        selectBTN->setObjectName("selectBTN");
        sizePolicy.setHeightForWidth(selectBTN->sizePolicy().hasHeightForWidth());
        selectBTN->setSizePolicy(sizePolicy);
        selectBTN->setMinimumSize(QSize(70, 43));
        selectBTN->setMaximumSize(QSize(70, 43));
        selectBTN->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    color: #3498db;\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"}"));

        horizontalLayout->addWidget(selectBTN);

        unzipBTN = new QPushButton(layoutWidget);
        unzipBTN->setObjectName("unzipBTN");
        sizePolicy.setHeightForWidth(unzipBTN->sizePolicy().hasHeightForWidth());
        unzipBTN->setSizePolicy(sizePolicy);
        unzipBTN->setMinimumSize(QSize(70, 43));
        unzipBTN->setMaximumSize(QSize(70, 43));
        unzipBTN->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    color: #3498db;\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"}"));

        horizontalLayout->addWidget(unzipBTN);

        deleteBTN = new QPushButton(layoutWidget);
        deleteBTN->setObjectName("deleteBTN");
        sizePolicy.setHeightForWidth(deleteBTN->sizePolicy().hasHeightForWidth());
        deleteBTN->setSizePolicy(sizePolicy);
        deleteBTN->setMinimumSize(QSize(70, 43));
        deleteBTN->setMaximumSize(QSize(70, 43));
        deleteBTN->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    color: #3498db;\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"}"));

        horizontalLayout->addWidget(deleteBTN);

        imgZipBTN = new QPushButton(layoutWidget);
        imgZipBTN->setObjectName("imgZipBTN");
        sizePolicy.setHeightForWidth(imgZipBTN->sizePolicy().hasHeightForWidth());
        imgZipBTN->setSizePolicy(sizePolicy);
        imgZipBTN->setMinimumSize(QSize(70, 43));
        imgZipBTN->setMaximumSize(QSize(70, 43));
        imgZipBTN->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: white;\n"
"    color: #3498db;\n"
"    border: 2px solid #3498db;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3498db;\n"
"    color: white;\n"
"}"));

        horizontalLayout->addWidget(imgZipBTN);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        backBTN = new QPushButton(layoutWidget);
        backBTN->setObjectName("backBTN");
        sizePolicy.setHeightForWidth(backBTN->sizePolicy().hasHeightForWidth());
        backBTN->setSizePolicy(sizePolicy);
        backBTN->setMinimumSize(QSize(25, 25));
        backBTN->setMaximumSize(QSize(25, 25));

        horizontalLayout_2->addWidget(backBTN);

        forwardBTN = new QPushButton(layoutWidget);
        forwardBTN->setObjectName("forwardBTN");
        sizePolicy.setHeightForWidth(forwardBTN->sizePolicy().hasHeightForWidth());
        forwardBTN->setSizePolicy(sizePolicy);
        forwardBTN->setMinimumSize(QSize(25, 25));
        forwardBTN->setMaximumSize(QSize(25, 25));

        horizontalLayout_2->addWidget(forwardBTN);

        refreshBTN = new QPushButton(layoutWidget);
        refreshBTN->setObjectName("refreshBTN");
        sizePolicy.setHeightForWidth(refreshBTN->sizePolicy().hasHeightForWidth());
        refreshBTN->setSizePolicy(sizePolicy);
        refreshBTN->setMinimumSize(QSize(25, 25));
        refreshBTN->setMaximumSize(QSize(25, 25));

        horizontalLayout_2->addWidget(refreshBTN);

        upBTN = new QPushButton(layoutWidget);
        upBTN->setObjectName("upBTN");
        sizePolicy.setHeightForWidth(upBTN->sizePolicy().hasHeightForWidth());
        upBTN->setSizePolicy(sizePolicy);
        upBTN->setMinimumSize(QSize(25, 25));
        upBTN->setMaximumSize(QSize(25, 25));

        horizontalLayout_2->addWidget(upBTN);

        pathEdit = new QLineEdit(layoutWidget);
        pathEdit->setObjectName("pathEdit");
        pathEdit->setMinimumSize(QSize(0, 25));

        horizontalLayout_2->addWidget(pathEdit);

        label = new QLabel(layoutWidget);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        filterEdit = new QLineEdit(layoutWidget);
        filterEdit->setObjectName("filterEdit");
        filterEdit->setMinimumSize(QSize(0, 25));

        horizontalLayout_2->addWidget(filterEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        fileTable = new QTableView(layoutWidget);
        fileTable->setObjectName("fileTable");
        fileTable->setStyleSheet(QString::fromUtf8("selection-color: white;                             /*\351\200\211\344\270\255\345\214\272\345\237\237\347\232\204\346\226\207\345\255\227\351\242\234\350\211\262*/selection-background-color: rgb(77, 77, 77);        /*\351\200\211\344\270\255\345\214\272\345\237\237\347\232\204\350\203\214\346\231\257\350\211\262*/"));
        fileTable->setDragEnabled(false);
        fileTable->setShowGrid(false);

        verticalLayout->addWidget(fileTable);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 820, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\345\216\213\347\274\251\345\267\245\345\205\267", nullptr));
        selectBTN->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251", nullptr));
        unzipBTN->setText(QCoreApplication::translate("MainWindow", "\350\247\243\345\216\213\345\210\260", nullptr));
        deleteBTN->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        imgZipBTN->setText(QCoreApplication::translate("MainWindow", "\345\233\276\347\211\207\345\216\213\347\274\251", nullptr));
        backBTN->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        forwardBTN->setText(QCoreApplication::translate("MainWindow", "\342\206\222", nullptr));
        refreshBTN->setText(QCoreApplication::translate("MainWindow", "\342\206\273", nullptr));
        upBTN->setText(QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        pathEdit->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
