/*
MediaPlayer/VLCController.h

Author(s):
Recep ALTIN (rcaltin @ gmail . com) 10.02.2019
*/

#pragma once

#include <QObject>
#include <QWidget>
#include <QTime>
#include <mutex>
#include "vlc/vlc.h"
#include "MediaFileReader.h"

typedef QPair<int, QString> MediaTrackInfo;
typedef QList<MediaTrackInfo> MediaTrackInfoList;

class VLCController : public QObject
{
	Q_OBJECT

public:
	~VLCController();
	static VLCController& getInstance();

	void vlcCallbacks(const libvlc_event_t * event, void * ptr);
	int vlcMediaOpenCallback(void * opaque, void ** datap, uint64_t * sizep);
	int vlcMediaReadCallback(void * opaque, unsigned char * buf, size_t len);
	int vlcMediaSeekCallback(void * opaque, uint64_t offset);
	void vlcMediaCloseCallback(void * opaque);

	void init(SecureMediaPlayerLib::MediaFileReader * mediaFileReader, QWidget * videoWidget = nullptr);
	void destroyMedia();
	bool isReadyToPlay();

	Q_INVOKABLE void playPauseMedia(bool play);
	bool isMediaPlaying();
	Q_INVOKABLE void stopMedia();

	void setMediaPosition(float position);
	float getMediaPosition();

	QTime getMediaTime();
	QTime getMediaTotalTime();

	MediaTrackInfoList getMediaVideoTracks();
	int getMediaVideoTrack();
	bool setMediaVideoTrack(int track_id);
	
	MediaTrackInfoList getMediaAudioTracks();
	int getMediaAudioTrack();
	bool setMediaAudioTrack(int track_id);
	
	MediaTrackInfoList getMediaSubtitleTracks();
	int getMediaSubtitleTrack();
	bool setMediaSubtitleTrack(int track_id);
	bool addMediaSubtitleFile(QString subtitleFilePath);

	void setMediaVolume(int volume);
	int getMediaVolume();

signals:
	void mediaPlaying();
	void mediaPaused();
	void mediaStopped();
	void mediaEndReached();
	void mediaPositionChanged(float position);
	void error(QString errorMessage);

private:
	VLCController();

	std::mutex m_callbackMutex;
	libvlc_instance_t * m_vlcInstance;
	libvlc_media_t * m_vlcMedia;
	libvlc_media_player_t * m_vlcMediaPlayer;
	libvlc_event_manager_t * m_vlcEventManager;
	SecureMediaPlayerLib::MediaFileReader * m_mediaFileReader;
	QWidget *m_videoWidget;
};
