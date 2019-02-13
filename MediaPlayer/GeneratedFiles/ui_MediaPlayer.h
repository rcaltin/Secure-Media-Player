/********************************************************************************
** Form generated from reading UI file 'MediaPlayer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEDIAPLAYER_H
#define UI_MEDIAPLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MediaPlayerClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_video;
    QFrame *frame_controls;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_media_time;
    QSlider *horizontalSlider_media_position;
    QLabel *label_media_time_total;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_media_play_pause;
    QPushButton *pushButton_media_stop;
    QFrame *line;
    QPushButton *pushButton_media_repeat;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *comboBox_video_track;
    QComboBox *comboBox_audio_track;
    QComboBox *comboBox_subtitle_track;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_vol;
    QSlider *horizontalSlider_media_volume;

    void setupUi(QMainWindow *MediaPlayerClass)
    {
        if (MediaPlayerClass->objectName().isEmpty())
            MediaPlayerClass->setObjectName(QStringLiteral("MediaPlayerClass"));
        MediaPlayerClass->resize(822, 714);
        MediaPlayerClass->setAcceptDrops(true);
        centralWidget = new QWidget(MediaPlayerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        frame_video = new QFrame(centralWidget);
        frame_video->setObjectName(QStringLiteral("frame_video"));
        frame_video->setMouseTracking(false);
        frame_video->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        frame_video->setFrameShape(QFrame::StyledPanel);
        frame_video->setFrameShadow(QFrame::Raised);

        verticalLayout_3->addWidget(frame_video);

        frame_controls = new QFrame(centralWidget);
        frame_controls->setObjectName(QStringLiteral("frame_controls"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_controls->sizePolicy().hasHeightForWidth());
        frame_controls->setSizePolicy(sizePolicy);
        frame_controls->setMaximumSize(QSize(16777215, 85));
        frame_controls->setFrameShape(QFrame::StyledPanel);
        frame_controls->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_controls);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_media_time = new QLabel(frame_controls);
        label_media_time->setObjectName(QStringLiteral("label_media_time"));
        label_media_time->setMinimumSize(QSize(60, 0));
        label_media_time->setMaximumSize(QSize(60, 16777215));
        label_media_time->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_media_time);

        horizontalSlider_media_position = new QSlider(frame_controls);
        horizontalSlider_media_position->setObjectName(QStringLiteral("horizontalSlider_media_position"));
        horizontalSlider_media_position->setEnabled(false);
        horizontalSlider_media_position->setMaximum(100000);
        horizontalSlider_media_position->setPageStep(10000);
        horizontalSlider_media_position->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSlider_media_position);

        label_media_time_total = new QLabel(frame_controls);
        label_media_time_total->setObjectName(QStringLiteral("label_media_time_total"));
        label_media_time_total->setMinimumSize(QSize(60, 0));
        label_media_time_total->setMaximumSize(QSize(60, 16777215));
        label_media_time_total->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_media_time_total);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton_media_play_pause = new QPushButton(frame_controls);
        pushButton_media_play_pause->setObjectName(QStringLiteral("pushButton_media_play_pause"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_media_play_pause->sizePolicy().hasHeightForWidth());
        pushButton_media_play_pause->setSizePolicy(sizePolicy1);
        pushButton_media_play_pause->setMaximumSize(QSize(28, 28));
        QIcon icon;
        icon.addFile(QStringLiteral(":/MediaPlayer/Resources/play.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_media_play_pause->setIcon(icon);
        pushButton_media_play_pause->setIconSize(QSize(48, 48));

        horizontalLayout_4->addWidget(pushButton_media_play_pause);

        pushButton_media_stop = new QPushButton(frame_controls);
        pushButton_media_stop->setObjectName(QStringLiteral("pushButton_media_stop"));
        pushButton_media_stop->setEnabled(false);
        sizePolicy1.setHeightForWidth(pushButton_media_stop->sizePolicy().hasHeightForWidth());
        pushButton_media_stop->setSizePolicy(sizePolicy1);
        pushButton_media_stop->setMaximumSize(QSize(28, 28));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/MediaPlayer/Resources/stop.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_media_stop->setIcon(icon1);
        pushButton_media_stop->setIconSize(QSize(48, 48));

        horizontalLayout_4->addWidget(pushButton_media_stop);

        line = new QFrame(frame_controls);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line);

        pushButton_media_repeat = new QPushButton(frame_controls);
        pushButton_media_repeat->setObjectName(QStringLiteral("pushButton_media_repeat"));
        sizePolicy1.setHeightForWidth(pushButton_media_repeat->sizePolicy().hasHeightForWidth());
        pushButton_media_repeat->setSizePolicy(sizePolicy1);
        pushButton_media_repeat->setMinimumSize(QSize(0, 0));
        pushButton_media_repeat->setMaximumSize(QSize(28, 28));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/MediaPlayer/Resources/repeat.png"), QSize(), QIcon::Normal, QIcon::On);
        pushButton_media_repeat->setIcon(icon2);
        pushButton_media_repeat->setIconSize(QSize(30, 30));
        pushButton_media_repeat->setCheckable(true);
        pushButton_media_repeat->setChecked(false);

        horizontalLayout_4->addWidget(pushButton_media_repeat);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        comboBox_video_track = new QComboBox(frame_controls);
        comboBox_video_track->setObjectName(QStringLiteral("comboBox_video_track"));
        comboBox_video_track->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox_video_track->sizePolicy().hasHeightForWidth());
        comboBox_video_track->setSizePolicy(sizePolicy2);
        comboBox_video_track->setMinimumSize(QSize(140, 0));

        horizontalLayout_4->addWidget(comboBox_video_track);

        comboBox_audio_track = new QComboBox(frame_controls);
        comboBox_audio_track->setObjectName(QStringLiteral("comboBox_audio_track"));
        comboBox_audio_track->setEnabled(false);
        sizePolicy2.setHeightForWidth(comboBox_audio_track->sizePolicy().hasHeightForWidth());
        comboBox_audio_track->setSizePolicy(sizePolicy2);
        comboBox_audio_track->setMinimumSize(QSize(140, 0));

        horizontalLayout_4->addWidget(comboBox_audio_track);

        comboBox_subtitle_track = new QComboBox(frame_controls);
        comboBox_subtitle_track->setObjectName(QStringLiteral("comboBox_subtitle_track"));
        comboBox_subtitle_track->setEnabled(false);
        sizePolicy2.setHeightForWidth(comboBox_subtitle_track->sizePolicy().hasHeightForWidth());
        comboBox_subtitle_track->setSizePolicy(sizePolicy2);
        comboBox_subtitle_track->setMinimumSize(QSize(140, 0));

        horizontalLayout_4->addWidget(comboBox_subtitle_track);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        label_vol = new QLabel(frame_controls);
        label_vol->setObjectName(QStringLiteral("label_vol"));
        label_vol->setPixmap(QPixmap(QString::fromUtf8(":/MediaPlayer/Resources/speaker_mute.png")));

        horizontalLayout_4->addWidget(label_vol);

        horizontalSlider_media_volume = new QSlider(frame_controls);
        horizontalSlider_media_volume->setObjectName(QStringLiteral("horizontalSlider_media_volume"));
        horizontalSlider_media_volume->setEnabled(false);
        sizePolicy1.setHeightForWidth(horizontalSlider_media_volume->sizePolicy().hasHeightForWidth());
        horizontalSlider_media_volume->setSizePolicy(sizePolicy1);
        horizontalSlider_media_volume->setMaximum(100);
        horizontalSlider_media_volume->setPageStep(10);
        horizontalSlider_media_volume->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(horizontalSlider_media_volume);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(frame_controls);

        MediaPlayerClass->setCentralWidget(centralWidget);

        retranslateUi(MediaPlayerClass);

        QMetaObject::connectSlotsByName(MediaPlayerClass);
    } // setupUi

    void retranslateUi(QMainWindow *MediaPlayerClass)
    {
        MediaPlayerClass->setWindowTitle(QApplication::translate("MediaPlayerClass", "Secure Media Player", nullptr));
        label_media_time->setText(QApplication::translate("MediaPlayerClass", "--:--:--", nullptr));
        label_media_time_total->setText(QApplication::translate("MediaPlayerClass", "--:--:--", nullptr));
        pushButton_media_play_pause->setText(QString());
        pushButton_media_stop->setText(QString());
        pushButton_media_repeat->setText(QString());
#ifndef QT_NO_TOOLTIP
        comboBox_video_track->setToolTip(QApplication::translate("MediaPlayerClass", "Video Track", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        comboBox_audio_track->setToolTip(QApplication::translate("MediaPlayerClass", "Audio Track", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        comboBox_subtitle_track->setToolTip(QApplication::translate("MediaPlayerClass", "Subtitle Track", nullptr));
#endif // QT_NO_TOOLTIP
        label_vol->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MediaPlayerClass: public Ui_MediaPlayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEDIAPLAYER_H
