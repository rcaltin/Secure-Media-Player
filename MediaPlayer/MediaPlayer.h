/*
MediaPlayer/MediaPlayer.h

Author(s):
Recep ALTIN (rcaltin @ gmail . com) 10.02.2019
*/

#pragma once

#include <QtWidgets/QMainWindow>
#include <QMouseEvent>
#include "ui_MediaPlayer.h"
#include "EncryptedMediaFileReader.h"

class MediaPlayer : public QMainWindow
{
	Q_OBJECT

public:
	MediaPlayer(QString mediaFile, QString password = QString(), QString subtitleFile = QString(), QWidget *parent = Q_NULLPTR);
	~MediaPlayer();

	void setFullscreen(bool fullscreen);

	bool play(QString mediaFilePath, QString subtitleFile = QString());

protected:
	void mouseDoubleClickEvent(QMouseEvent *event);

private:
	bool eventFilter(QObject * object, QEvent * ev);
	void dragEnterEvent(QDragEnterEvent * ev);
	void dropEvent(QDropEvent * ev);
	
	Ui::MediaPlayerClass ui;
	SecureMediaPlayerLib::MediaFileReader * m_mediaFileReader;
	QString m_mediaPassword;
	Qt::WindowFlags m_originalWindowFlags;
	bool m_mediaInfoParsed;
	bool m_mediaEndReached;
	static const QStringList sm_supportedSubtitleFiles;

public slots:
	void vlcMediaPlaying();
	void vlcMediaPaused();
	void vlcMediaStopped();
	void vlcMediaEndReached();
	void vlcMediaPositionChanged(float position);
	void vlcError(QString error);

	void on_pushButton_media_play_pause_clicked();
	void on_pushButton_media_stop_clicked();
	void on_pushButton_media_repeat_clicked();
	void on_horizontalSlider_media_position_valueChanged(int value);
	void on_horizontalSlider_media_volume_valueChanged(int value);
	void on_comboBox_video_track_currentIndexChanged(int index);
	void on_comboBox_audio_track_currentIndexChanged(int index);
	void on_comboBox_subtitle_track_currentIndexChanged(int index);
};