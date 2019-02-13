/********************************************************************************
** Form generated from reading UI file 'MediaConverter.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDIACONVERTER_H
#define UI_MEDIACONVERTER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MediaConverterClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_in;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_browseIn;
    QPushButton *pushButton_browseIn;
    QGridLayout *gridLayout;
    QLabel *label_passwordIn;
    QLineEdit *lineEdit_passwordIn;
    QGroupBox *groupBox_out;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_browseOut;
    QPushButton *pushButton_browseOut;
    QGridLayout *gridLayout_2;
    QLabel *label_passwordOut;
    QLineEdit *lineEdit_passwordOut;
    QLabel *label_passwordValidationOut;
    QLineEdit *lineEdit_passwordValidationOut;
    QHBoxLayout *horizontalLayout_3;
    QProgressBar *progressBar_progress;
    QPushButton *pushButton_startCancel;

    void setupUi(QMainWindow *MediaConverterClass)
    {
        if (MediaConverterClass->objectName().isEmpty())
            MediaConverterClass->setObjectName(QStringLiteral("MediaConverterClass"));
        MediaConverterClass->resize(500, 350);
        MediaConverterClass->setMinimumSize(QSize(500, 350));
        MediaConverterClass->setMaximumSize(QSize(500, 350));
        centralWidget = new QWidget(MediaConverterClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_in = new QGroupBox(centralWidget);
        groupBox_in->setObjectName(QStringLiteral("groupBox_in"));
        verticalLayout = new QVBoxLayout(groupBox_in);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit_browseIn = new QLineEdit(groupBox_in);
        lineEdit_browseIn->setObjectName(QStringLiteral("lineEdit_browseIn"));

        horizontalLayout->addWidget(lineEdit_browseIn);

        pushButton_browseIn = new QPushButton(groupBox_in);
        pushButton_browseIn->setObjectName(QStringLiteral("pushButton_browseIn"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/MediaConverter/Resources/browse.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_browseIn->setIcon(icon);

        horizontalLayout->addWidget(pushButton_browseIn);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_passwordIn = new QLabel(groupBox_in);
        label_passwordIn->setObjectName(QStringLiteral("label_passwordIn"));

        gridLayout->addWidget(label_passwordIn, 0, 0, 1, 1);

        lineEdit_passwordIn = new QLineEdit(groupBox_in);
        lineEdit_passwordIn->setObjectName(QStringLiteral("lineEdit_passwordIn"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_passwordIn->sizePolicy().hasHeightForWidth());
        lineEdit_passwordIn->setSizePolicy(sizePolicy);
        lineEdit_passwordIn->setMinimumSize(QSize(200, 0));
        lineEdit_passwordIn->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_passwordIn, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        verticalLayout_3->addWidget(groupBox_in);

        groupBox_out = new QGroupBox(centralWidget);
        groupBox_out->setObjectName(QStringLiteral("groupBox_out"));
        verticalLayout_2 = new QVBoxLayout(groupBox_out);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lineEdit_browseOut = new QLineEdit(groupBox_out);
        lineEdit_browseOut->setObjectName(QStringLiteral("lineEdit_browseOut"));

        horizontalLayout_2->addWidget(lineEdit_browseOut);

        pushButton_browseOut = new QPushButton(groupBox_out);
        pushButton_browseOut->setObjectName(QStringLiteral("pushButton_browseOut"));
        pushButton_browseOut->setIcon(icon);

        horizontalLayout_2->addWidget(pushButton_browseOut);


        verticalLayout_2->addLayout(horizontalLayout_2);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_passwordOut = new QLabel(groupBox_out);
        label_passwordOut->setObjectName(QStringLiteral("label_passwordOut"));

        gridLayout_2->addWidget(label_passwordOut, 0, 0, 1, 1);

        lineEdit_passwordOut = new QLineEdit(groupBox_out);
        lineEdit_passwordOut->setObjectName(QStringLiteral("lineEdit_passwordOut"));
        sizePolicy.setHeightForWidth(lineEdit_passwordOut->sizePolicy().hasHeightForWidth());
        lineEdit_passwordOut->setSizePolicy(sizePolicy);
        lineEdit_passwordOut->setMinimumSize(QSize(200, 0));
        lineEdit_passwordOut->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(lineEdit_passwordOut, 0, 1, 1, 1);

        label_passwordValidationOut = new QLabel(groupBox_out);
        label_passwordValidationOut->setObjectName(QStringLiteral("label_passwordValidationOut"));

        gridLayout_2->addWidget(label_passwordValidationOut, 1, 0, 1, 1);

        lineEdit_passwordValidationOut = new QLineEdit(groupBox_out);
        lineEdit_passwordValidationOut->setObjectName(QStringLiteral("lineEdit_passwordValidationOut"));
        sizePolicy.setHeightForWidth(lineEdit_passwordValidationOut->sizePolicy().hasHeightForWidth());
        lineEdit_passwordValidationOut->setSizePolicy(sizePolicy);
        lineEdit_passwordValidationOut->setMinimumSize(QSize(200, 0));
        lineEdit_passwordValidationOut->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(lineEdit_passwordValidationOut, 1, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        verticalLayout_3->addWidget(groupBox_out);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        progressBar_progress = new QProgressBar(centralWidget);
        progressBar_progress->setObjectName(QStringLiteral("progressBar_progress"));
        progressBar_progress->setValue(0);

        horizontalLayout_3->addWidget(progressBar_progress);

        pushButton_startCancel = new QPushButton(centralWidget);
        pushButton_startCancel->setObjectName(QStringLiteral("pushButton_startCancel"));
        pushButton_startCancel->setEnabled(false);
        pushButton_startCancel->setMinimumSize(QSize(100, 0));
        pushButton_startCancel->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_3->addWidget(pushButton_startCancel);


        verticalLayout_3->addLayout(horizontalLayout_3);

        MediaConverterClass->setCentralWidget(centralWidget);

        retranslateUi(MediaConverterClass);

        QMetaObject::connectSlotsByName(MediaConverterClass);
    } // setupUi

    void retranslateUi(QMainWindow *MediaConverterClass)
    {
        MediaConverterClass->setWindowTitle(QApplication::translate("MediaConverterClass", "Secure Media Converter", nullptr));
        groupBox_in->setTitle(QApplication::translate("MediaConverterClass", "Input Media", nullptr));
        pushButton_browseIn->setText(QString());
        label_passwordIn->setText(QApplication::translate("MediaConverterClass", "Password", nullptr));
        groupBox_out->setTitle(QApplication::translate("MediaConverterClass", "Output Media", nullptr));
        pushButton_browseOut->setText(QString());
        label_passwordOut->setText(QApplication::translate("MediaConverterClass", "Password", nullptr));
        label_passwordValidationOut->setText(QApplication::translate("MediaConverterClass", "Password (Validation)", nullptr));
        pushButton_startCancel->setText(QApplication::translate("MediaConverterClass", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MediaConverterClass: public Ui_MediaConverterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIACONVERTER_H
