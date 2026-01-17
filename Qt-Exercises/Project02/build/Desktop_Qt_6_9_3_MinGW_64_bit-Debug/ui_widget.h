/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *addButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *deleteButton;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_10;
    QPushButton *headshotSelectButton;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QDateEdit *dateEdit;
    QSpacerItem *horizontalSpacer_3;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *textEdit_2;
    QTextEdit *textEdit_3;
    QTextEdit *textEdit_4;
    QTextEdit *textEdit_5;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QComboBox *comboBox_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *saveButton;
    QPushButton *exportButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(820, 640);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        Widget->setMinimumSize(QSize(820, 640));
        Widget->setMaximumSize(QSize(820, 640));
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 10, 251, 571));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(layoutWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setDragEnabled(true);

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        addButton = new QPushButton(layoutWidget);
        addButton->setObjectName("addButton");

        horizontalLayout->addWidget(addButton);

        horizontalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        deleteButton = new QPushButton(layoutWidget);
        deleteButton->setObjectName("deleteButton");

        horizontalLayout->addWidget(deleteButton);


        verticalLayout->addLayout(horizontalLayout);

        layoutWidget1 = new QWidget(Widget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(710, 10, 91, 161));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget1);
        label_10->setObjectName("label_10");

        verticalLayout_3->addWidget(label_10);

        headshotSelectButton = new QPushButton(layoutWidget1);
        headshotSelectButton->setObjectName("headshotSelectButton");

        verticalLayout_3->addWidget(headshotSelectButton);

        layoutWidget2 = new QWidget(Widget);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(311, 11, 391, 111));
        gridLayout = new QGridLayout(layoutWidget2);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName("label_2");

        horizontalLayout_4->addWidget(label_2);

        lineEdit_2 = new QLineEdit(layoutWidget2);
        lineEdit_2->setObjectName("lineEdit_2");

        horizontalLayout_4->addWidget(lineEdit_2);


        gridLayout->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(layoutWidget2);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        comboBox = new QComboBox(layoutWidget2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");

        horizontalLayout_3->addWidget(comboBox);

        horizontalSpacer_2 = new QSpacerItem(50, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(layoutWidget2);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(layoutWidget2);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_2->addWidget(lineEdit);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName("label_4");

        horizontalLayout_5->addWidget(label_4);

        dateEdit = new QDateEdit(layoutWidget2);
        dateEdit->setObjectName("dateEdit");

        horizontalLayout_5->addWidget(dateEdit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout_5, 1, 1, 1, 1);

        layoutWidget3 = new QWidget(Widget);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(310, 170, 391, 421));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_6 = new QLabel(layoutWidget3);
        label_6->setObjectName("label_6");

        verticalLayout_2->addWidget(label_6);

        label_7 = new QLabel(layoutWidget3);
        label_7->setObjectName("label_7");

        verticalLayout_2->addWidget(label_7);

        label_8 = new QLabel(layoutWidget3);
        label_8->setObjectName("label_8");

        verticalLayout_2->addWidget(label_8);

        label_9 = new QLabel(layoutWidget3);
        label_9->setObjectName("label_9");

        verticalLayout_2->addWidget(label_9);


        horizontalLayout_7->addLayout(verticalLayout_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        textEdit_2 = new QTextEdit(layoutWidget3);
        textEdit_2->setObjectName("textEdit_2");

        verticalLayout_4->addWidget(textEdit_2);

        textEdit_3 = new QTextEdit(layoutWidget3);
        textEdit_3->setObjectName("textEdit_3");

        verticalLayout_4->addWidget(textEdit_3);

        textEdit_4 = new QTextEdit(layoutWidget3);
        textEdit_4->setObjectName("textEdit_4");

        verticalLayout_4->addWidget(textEdit_4);

        textEdit_5 = new QTextEdit(layoutWidget3);
        textEdit_5->setObjectName("textEdit_5");

        verticalLayout_4->addWidget(textEdit_5);


        horizontalLayout_7->addLayout(verticalLayout_4);

        layoutWidget4 = new QWidget(Widget);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(312, 131, 219, 27));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget4);
        label_5->setObjectName("label_5");

        horizontalLayout_6->addWidget(label_5);

        comboBox_2 = new QComboBox(layoutWidget4);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName("comboBox_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(50);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_2->sizePolicy().hasHeightForWidth());
        comboBox_2->setSizePolicy(sizePolicy1);
        comboBox_2->setMinimumSize(QSize(140, 25));
        comboBox_2->setMaximumSize(QSize(140, 25));

        horizontalLayout_6->addWidget(comboBox_2);

        widget = new QWidget(Widget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(520, 600, 187, 29));
        horizontalLayout_8 = new QHBoxLayout(widget);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        saveButton = new QPushButton(widget);
        saveButton->setObjectName("saveButton");

        horizontalLayout_8->addWidget(saveButton);

        exportButton = new QPushButton(widget);
        exportButton->setObjectName("exportButton");

        horizontalLayout_8->addWidget(exportButton);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "\346\210\220\345\221\230\346\241\243\346\241\210\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        addButton->setText(QCoreApplication::translate("Widget", "\346\267\273\345\212\240", nullptr));
        deleteButton->setText(QCoreApplication::translate("Widget", "\345\210\240\351\231\244", nullptr));
        label_10->setText(QCoreApplication::translate("Widget", "TextLabel", nullptr));
        headshotSelectButton->setText(QCoreApplication::translate("Widget", "\351\200\211\346\213\251\347\205\247\347\211\207", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "\347\261\215\350\264\257\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\346\200\247\345\210\253\357\274\232", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Widget", "\347\224\267", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Widget", "\345\245\263", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Widget", "\346\262\203\345\260\224\347\216\233\345\241\221\346\226\231\350\242\213", nullptr));

        label->setText(QCoreApplication::translate("Widget", "\345\247\223\345\220\215\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "\345\207\272\347\224\237\346\227\245\346\234\237\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("Widget", "\345\256\266\345\272\255\344\275\217\345\235\200\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("Widget", "\346\225\231\350\202\262\347\273\217\345\216\206\357\274\232", nullptr));
        label_8->setText(QCoreApplication::translate("Widget", "\350\216\267\345\276\227\345\245\226\351\241\271\357\274\232", nullptr));
        label_9->setText(QCoreApplication::translate("Widget", "\347\211\271\351\225\277\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "\346\224\277\346\262\273\351\235\242\350\262\214\357\274\232", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("Widget", "\347\276\244\344\274\227", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("Widget", "\345\205\261\351\235\222\345\233\242\345\221\230", nullptr));
        comboBox_2->setItemText(2, QCoreApplication::translate("Widget", "\344\270\255\345\233\275\345\205\261\344\272\247\345\205\232\345\205\232\345\221\230", nullptr));

        saveButton->setText(QCoreApplication::translate("Widget", "\344\277\235\345\255\230", nullptr));
        exportButton->setText(QCoreApplication::translate("Widget", "\345\257\274\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
