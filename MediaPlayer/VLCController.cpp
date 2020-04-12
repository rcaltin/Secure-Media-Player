#include "VLCController.h"

using namespace SecureMediaPlayerLib;

#pragma region Callback Wrappers
extern "C" void vlcCallbacksGateway(const libvlc_event_t * event, void * ptr)
{
	VLCController::getInstance().vlcCallbacks(event, ptr);
}

extern "C" int vlcMediaOpenCallbackGateway(void * opaque, void ** datap, uint64_t * sizep)
{
	return VLCController::getInstance().vlcMediaOpenCallback(opaque, datap, sizep);
}

extern "C" int vlcMediaReadCallbackGateway(void * opaque, unsigned char * buf, size_t len)
{
	return VLCController::getInstance().vlcMediaReadCallback(opaque, buf, len);
}

extern "C" int vlcMediaSeekCallbackGateway(void * opaque, uint64_t offset)
{
	return VLCController::getInstance().vlcMediaSeekCallback(opaque, offset);
}

extern "C" void vlcMediaCloseCallbackGateway(void * opaque)
{
	VLCController::getInstance().vlcMediaCloseCallback(opaque);
}
#pragma endregion

VLCController::VLCController()
	: QObject(nullptr),
	m_vlcInstance(nullptr),
	m_vlcMedia(nullptr),
	m_vlcMediaPlayer(nullptr),
	m_vlcEventManager(nullptr)
{
}

VLCController::~VLCController()
{
}

VLCController& VLCController::getInstance()
{
	static VLCController instance;
	return instance;
}

void VLCController::init(MediaFileReader * mediaFileReader, QWidget *videoWidget)
{
	m_mediaFileReader = mediaFileReader;
	m_videoWidget = videoWidget;

	m_vlcInstance = libvlc_new(0, NULL);

	m_vlcMedia = libvlc_media_new_callbacks(
		m_vlcInstance,
		vlcMediaOpenCallbackGateway,
		vlcMediaReadCallbackGateway,
		vlcMediaSeekCallbackGateway,
		vlcMediaCloseCallbackGateway,
		0
	);

	m_vlcMediaPlayer = libvlc_media_player_new_from_media(m_vlcMedia);

	//TODO: consider reactivate for osd menu
	libvlc_video_set_mouse_input(m_vlcMediaPlayer, 0);
	libvlc_video_set_key_input(m_vlcMediaPlayer, 0);
	// ~

#if defined(Q_OS_WIN)
	libvlc_media_player_set_hwnd(m_vlcMediaPlayer, m_videoWidget ? (void*)m_videoWidget->winId() : nullptr);
#elif defined(Q_OS_MAC)
	libvlc_media_player_set_nsobject(m_vlcMediaPlayer, m_videoWidget ? (void*)m_videoWidget->winId() : nullptr);
#elif defined(Q_OS_LINUX)
	libvlc_media_player_set_xwindow(m_vlcMediaPlayer, m_videoWidget ? reinterpret_cast<intptr_t>(m_videoWidget->winId()) : nullptr);
#endif

	m_vlcEventManager = libvlc_media_player_event_manager(m_vlcMediaPlayer);
	libvlc_event_attach(m_vlcEventManager, libvlc_MediaPlayerPlaying, vlcCallbacksGateway, 0);
	libvlc_event_attach(m_vlcEventManager, libvlc_MediaPlayerPaused, vlcCallbacksGateway, 0);
	libvlc_event_attach(m_vlcEventManager, libvlc_MediaPlayerStopped, vlcCallbacksGateway, 0);
	libvlc_event_attach(m_vlcEventManager, libvlc_MediaPlayerEndReached, vlcCallbacksGateway, 0);
	libvlc_event_attach(m_vlcEventManager, libvlc_MediaPlayerPositionChanged, vlcCallbacksGateway, 0);

	m_mediaFileReader->seek(0);
}

void VLCController::destroyMedia()
{
	if (!m_vlcInstance)
		return;

	libvlc_event_detach(m_vlcEventManager, libvlc_MediaPlayerPlaying, vlcCallbacksGateway, 0);
	libvlc_event_detach(m_vlcEventManager, libvlc_MediaPlayerPaused, vlcCallbacksGateway, 0);
	libvlc_event_detach(m_vlcEventManager, libvlc_MediaPlayerStopped, vlcCallbacksGateway, 0);
	libvlc_event_detach(m_vlcEventManager, libvlc_MediaPlayerEndReached, vlcCallbacksGateway, 0);
	libvlc_event_detach(m_vlcEventManager, libvlc_MediaPlayerPositionChanged, vlcCallbacksGateway, 0);

	if (m_vlcMediaPlayer)
	{
		libvlc_media_player_stop(m_vlcMediaPlayer);
		libvlc_media_player_release(m_vlcMediaPlayer);
		m_vlcMediaPlayer = nullptr;
	}

	libvlc_release(m_vlcInstance);
	m_vlcInstance = nullptr;
}

bool VLCController::isReadyToPlay()
{
	return m_vlcInstance && m_vlcMediaPlayer && m_vlcMedia;
}

void VLCController::playPauseMedia(bool play)
{
	play ? libvlc_media_player_play(m_vlcMediaPlayer) : libvlc_media_player_pause(m_vlcMediaPlayer);
}

bool VLCController::isMediaPlaying()
{
	return libvlc_media_player_is_playing(m_vlcMediaPlayer);
}

void VLCController::stopMedia()
{
	libvlc_media_player_stop(m_vlcMediaPlayer);
}

void VLCController::setMediaPosition(float position)
{
	libvlc_media_player_set_position(m_vlcMediaPlayer, position);
}

float VLCController::getMediaPosition()
{
	return libvlc_media_player_get_position(m_vlcMediaPlayer);
}

QTime VLCController::getMediaTime()
{
	return QTime::fromMSecsSinceStartOfDay((int)libvlc_media_player_get_time(m_vlcMediaPlayer));
}

QTime VLCController::getMediaTotalTime()
{
	return QTime::fromMSecsSinceStartOfDay((int)libvlc_media_player_get_length(m_vlcMediaPlayer));
}

MediaTrackInfoList VLCController::getMediaVideoTracks()
{
	MediaTrackInfoList tracks;

	libvlc_track_description_t * track = libvlc_video_get_track_description(m_vlcMediaPlayer);

	while (track)
	{
		tracks.push_back(qMakePair<int, QString>(track->i_id, QString(track->psz_name)));
		track = track->p_next;
	}

	return tracks;
}

int VLCController::getMediaVideoTrack()
{
	return libvlc_video_get_track(m_vlcMediaPlayer);
}

bool VLCController::setMediaVideoTrack(int track_id)
{
	return libvlc_video_set_track(m_vlcMediaPlayer, track_id) == 0;
}

MediaTrackInfoList VLCController::getMediaAudioTracks()
{
	MediaTrackInfoList tracks;

	libvlc_track_description_t *track = libvlc_audio_get_track_description(m_vlcMediaPlayer);

	while (track)
	{
		tracks.push_back(qMakePair<int, QString>(track->i_id, QString(track->psz_name)));
		track = track->p_next;
	}

	return tracks;
}

int VLCController::getMediaAudioTrack()
{
	return libvlc_audio_get_track(m_vlcMediaPlayer);
}

bool VLCController::setMediaAudioTrack(int track_id)
{
	return libvlc_audio_set_track(m_vlcMediaPlayer, track_id) == 0;
}

MediaTrackInfoList VLCController::getMediaSubtitleTracks()
{
	MediaTrackInfoList tracks;

	libvlc_track_description_t *track = libvlc_video_get_spu_description(m_vlcMediaPlayer);

	while (track)
	{
		tracks.push_back(qMakePair<int, QString>(track->i_id, QString(track->psz_name)));
		track = track->p_next;
	}

	return tracks;
}

int VLCController::getMediaSubtitleTrack()
{
	return libvlc_video_get_spu(m_vlcMediaPlayer);
}

bool VLCController::setMediaSubtitleTrack(int track_id)
{
	return libvlc_video_set_spu(m_vlcMediaPlayer, track_id) == 0;
}

void VLCController::setMediaVolume(int volume)
{
	libvlc_audio_set_volume(m_vlcMediaPlayer, volume);
}

int VLCController::getMediaVolume()
{
	return libvlc_audio_get_volume(m_vlcMediaPlayer);
}

bool VLCController::addMediaSubtitleFile(QString subtitleFilePath)
{
	//return libvlc_media_player_add_slave(m_vlcMediaPlayer, libvlc_media_slave_type_subtitle, subtitleFilePath.toStdString().c_str(), true); // proper usage, but looks not working
	return libvlc_video_set_subtitle_file(m_vlcMediaPlayer, subtitleFilePath.toStdString().c_str()); // deprecated usage
}

void VLCController::vlcCallbacks(const libvlc_event_t * event, void * ptr)
{
	std::lock_guard<std::mutex> lock(m_callbackMutex);

	switch (event->type)
	{
	case libvlc_MediaPlayerPlaying:
		emit mediaPlaying();
		break;

	case libvlc_MediaPlayerPaused:
		emit mediaPaused();
		break;

	case libvlc_MediaPlayerStopped:
		emit mediaStopped();
		break;

	case libvlc_MediaPlayerEndReached:
		emit mediaEndReached();
		break;

	case libvlc_MediaPlayerPositionChanged:
		emit mediaPositionChanged(event->u.media_player_position_changed.new_position);
		break;

	case libvlc_MediaPlayerEncounteredError:
		emit error(tr("libVLC error."));
		break;
	}
}

int VLCController::vlcMediaOpenCallback(void * opaque, void ** datap, uint64_t * sizep)
{
	std::lock_guard<std::mutex> lock(m_callbackMutex);

	// optional, if comment out libvlc will trigger the 'vlcMediaReadCallback' as more often but for less buffer length
	*sizep = m_mediaFileReader->mediaLength();

	return 0;
}

int VLCController::vlcMediaReadCallback(void * opaque, unsigned char * buf, size_t len)
{
	std::lock_guard<std::mutex> lock(m_callbackMutex);

	return m_mediaFileReader->read(buf, len);
}

int VLCController::vlcMediaSeekCallback(void * opaque, uint64_t offset)
{
	std::lock_guard<std::mutex> lock(m_callbackMutex);

	// important for some media types which holds meta data at the end of the file, for example: .mp4
	m_mediaFileReader->seek(offset);

	return 0;
}

void VLCController::vlcMediaCloseCallback(void * opaque)
{
	std::lock_guard<std::mutex> lock(m_callbackMutex);

	m_mediaFileReader->seek(0);

	QMetaObject::invokeMethod(&getInstance(), "stopMedia");
}