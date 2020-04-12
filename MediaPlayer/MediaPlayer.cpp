#include "MediaPlayer.h"
#include "MediaFileFactory.h"
#include "VLCController.h"
#include "CryptographyManager.h"
#include <QWindow>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>
#include <QMimeData>

using namespace SecureMediaPlayerLib;

const QStringList MediaPlayer::sm_supportedSubtitleFiles = {
	"aqt", "cvd", "dks", "jss", "sub", "ttxt", "mpl", "sub", "pjs", "psb", "rt", "smi", "ssf", "srt", "ssa", "sub", "svcd", "usf", "idx", "txt"
};

MediaPlayer::MediaPlayer(QString mediaFilePath, QString mediaPassword, QString subtitleFile, QWidget *parent)
	: QMainWindow(parent), m_mediaPassword(mediaPassword), m_mediaInfoParsed(false), m_mediaEndReached(false), m_mediaFileReader(nullptr)
{
	ui.setupUi(this);

	m_originalWindowFlags = this->windowFlags();

	qApp->installEventFilter(this);

	VLCController * vlc = &VLCController::getInstance();
	connect(vlc, SIGNAL(mediaPlaying()), this, SLOT(vlcMediaPlaying()));
	connect(vlc, SIGNAL(mediaPaused()), this, SLOT(vlcMediaPaused()));
	connect(vlc, SIGNAL(mediaStopped()), this, SLOT(vlcMediaStopped()));
	connect(vlc, SIGNAL(mediaEndReached()), this, SLOT(vlcMediaEndReached()));
	connect(vlc, SIGNAL(mediaPositionChanged(float)), this, SLOT(vlcMediaPositionChanged(float)));
	connect(vlc, SIGNAL(error(QString)), this, SLOT(vlcError(QString)));

	if (!mediaFilePath.isEmpty() && !play(mediaFilePath, subtitleFile))
		exit(-1);
}

MediaPlayer::~MediaPlayer()
{
	VLCController::getInstance().destroyMedia();

	if (m_mediaFileReader)
		delete m_mediaFileReader;
}

void MediaPlayer::setFullscreen(bool fullscreen)
{
	if (fullscreen)
	{
		ui.frame_controls->hide();
		this->windowHandle()->setFlags(Qt::FramelessWindowHint);
		this->windowHandle()->showFullScreen();
	}
	else
	{
		this->showNormal();
		this->windowHandle()->setFlags(m_originalWindowFlags);
		ui.frame_controls->show();
	}
}

bool MediaPlayer::play(QString mediaFilePath, QString subtitleFile)
{
	if (VLCController::getInstance().isReadyToPlay())
	{
		VLCController::getInstance().destroyMedia();

		if (m_mediaFileReader)
			delete m_mediaFileReader;
	}

	// load the media file
	if (!mediaFilePath.isEmpty())
	{
		m_mediaFileReader = MediaFileFactory::createMediaFileReader(mediaFilePath);
		VLCController * vlc = &VLCController::getInstance();

		if (m_mediaFileReader->isSecureMedia())
		{
			if (m_mediaPassword.isEmpty())
				m_mediaPassword = QInputDialog::getText(this, tr(MEDIA_FILE_EXTENSION), tr("Enter Media Password"), QLineEdit::Password);

			static_cast<EncryptedMediaFileReader*>(m_mediaFileReader)->setMediaPasswordHash(CryptographyManager::SHA3_256(m_mediaPassword));
		}

		// try open the media file
		if (!m_mediaFileReader->open())
		{
			QMessageBox::critical(this, tr("Error"), tr("Media file couldn't be opened."));

			delete m_mediaFileReader;
			m_mediaFileReader = nullptr;

			return false;
		}
		else
		{
			// init vlc wrapper
			vlc->init(m_mediaFileReader, ui.frame_video);

			// play on start
			on_pushButton_media_play_pause_clicked();

			// add subtitle file
			if (!subtitleFile.isEmpty() && sm_supportedSubtitleFiles.contains(subtitleFile.split('.').takeLast()))
				vlc->addMediaSubtitleFile(subtitleFile);
		}
	}

	return true;
}

void MediaPlayer::mouseDoubleClickEvent(QMouseEvent *event)
{
	QWidget::mouseDoubleClickEvent(event);
	setFullscreen(!isFullScreen());
}

bool MediaPlayer::eventFilter(QObject *object, QEvent *ev)
{
	if (ev->type() == QEvent::KeyPress && VLCController::getInstance().isReadyToPlay())
	{
		int key = static_cast<QKeyEvent*>(ev)->key();

		if (key == Qt::Key_F11 || key == Qt::Key_Enter || key == Qt::Key_Return)
		{
			setFullscreen(!this->isFullScreen());
			return true;
		}
		else if (key == Qt::Key_Escape && this->isFullScreen())
		{
			setFullscreen(false);
			return true;
		}
		else if (key == Qt::Key_Space || key == Qt::Key_P)
		{
			on_pushButton_media_play_pause_clicked();
			return true;
		}
		else if (key == Qt::Key_S)
		{
			on_pushButton_media_stop_clicked();
			return true;
		}
		else if (key == Qt::Key_R)
		{
			ui.pushButton_media_repeat->setChecked(!ui.pushButton_media_repeat->isChecked());
			return true;
		}
		else if (key == Qt::Key_Left && ui.horizontalSlider_media_position->isEnabled())
		{
			ui.horizontalSlider_media_position->setValue(ui.horizontalSlider_media_position->value() - ui.horizontalSlider_media_position->pageStep());
			return true;
		}
		else if (key == Qt::Key_Right && ui.horizontalSlider_media_position->isEnabled())
		{
			ui.horizontalSlider_media_position->setValue(ui.horizontalSlider_media_position->value() + ui.horizontalSlider_media_position->pageStep());
			return true;
		}
		else if (key == Qt::Key_Z && ui.horizontalSlider_media_volume->isEnabled())
		{
			ui.horizontalSlider_media_volume->setValue(ui.horizontalSlider_media_volume->value() - ui.horizontalSlider_media_volume->pageStep());
			return true;
		}
		else if (key == Qt::Key_A && ui.horizontalSlider_media_volume->isEnabled())
		{
			ui.horizontalSlider_media_volume->setValue(ui.horizontalSlider_media_volume->value() + ui.horizontalSlider_media_volume->pageStep());
			return true;
		}
	}

	return false;
}

void MediaPlayer::dragEnterEvent(QDragEnterEvent * ev)
{
	//// accept only supported subtitle files which are defined in sm_supportedSubtitleFiles
	//bool accept = true;
	//if (ev->mimeData()->hasUrls() && VLCController::getInstance().isReadyToPlay())
	//{
	//	for each(QUrl url in ev->mimeData()->urls())
	//	{
	//		QString dir = QDir::toNativeSeparators(url.path());
	//		if (!sm_supportedSubtitleFiles.contains(dir.split('.').takeLast()))
	//		{
	//			accept = false;
	//			break;
	//		}
	//	}
	//}
	//else
	//	accept = false;

	//if(accept)
		ev->acceptProposedAction();
}

void MediaPlayer::dropEvent(QDropEvent * ev)
{
	if (ev->mimeData()->hasUrls())
	{
		for(QUrl url : ev->mimeData()->urls())
		{
			if (sm_supportedSubtitleFiles.contains(url.toLocalFile().split('.').takeLast()))
			{
				if (VLCController::getInstance().isReadyToPlay())
				{
					VLCController::getInstance().addMediaSubtitleFile(url.toLocalFile());
					m_mediaInfoParsed = false; // force reload subtitles
				}
			}
			else
			{
				play(url.toLocalFile());
			}
		}

		ev->acceptProposedAction();
	}
}

void MediaPlayer::vlcMediaPlaying()
{
	ui.pushButton_media_stop->setEnabled(true);
	ui.horizontalSlider_media_position->setEnabled(true);
	ui.horizontalSlider_media_volume->setEnabled(true);
	ui.pushButton_media_play_pause->setIcon(QIcon(":/MediaPlayer/Resources/pause.png"));
}

void MediaPlayer::vlcMediaPaused()
{
	ui.pushButton_media_play_pause->setIcon(QIcon(":/MediaPlayer/Resources/play.png"));
}

void MediaPlayer::vlcMediaStopped()
{
	m_mediaInfoParsed = false;
	ui.pushButton_media_stop->setEnabled(false);
	ui.horizontalSlider_media_position->setEnabled(false);
	ui.horizontalSlider_media_volume->setEnabled(false);
	ui.pushButton_media_play_pause->setIcon(QIcon(":/MediaPlayer/Resources/play.png"));
	ui.label_media_time->setText("00:00:00");

	ui.horizontalSlider_media_position->blockSignals(true);
	ui.horizontalSlider_media_position->setValue(0);
	ui.horizontalSlider_media_position->blockSignals(false);

	if (m_mediaEndReached && ui.pushButton_media_repeat->isChecked())
	{
		m_mediaEndReached = false;
		on_pushButton_media_play_pause_clicked();
	}
}

void MediaPlayer::vlcMediaEndReached()
{
	m_mediaEndReached = true;
}

void MediaPlayer::vlcMediaPositionChanged(float position)
{
	// parse media info after play
	if (!m_mediaInfoParsed)
	{
		// video track
		int ind = -1, track = VLCController::getInstance().getMediaVideoTrack();
		ui.comboBox_video_track->blockSignals(true);
		ui.comboBox_video_track->clear();
		for each (QPair<int, QString> item in VLCController::getInstance().getMediaVideoTracks())
		{
			if (track == item.first)
				ind = ui.comboBox_video_track->count();

			ui.comboBox_video_track->addItem(item.second, item.first);
		}
		ui.comboBox_video_track->setCurrentIndex(ind);
		ui.comboBox_video_track->blockSignals(false);
		ui.comboBox_video_track->setEnabled(ind >= 0);

		// audio track
		ind = -1;
		track = VLCController::getInstance().getMediaAudioTrack();
		ui.comboBox_audio_track->blockSignals(true);
		ui.comboBox_audio_track->clear();
		for each (QPair<int, QString> item in VLCController::getInstance().getMediaAudioTracks())
		{
			if (track == item.first)
				ind = ui.comboBox_audio_track->count();

			ui.comboBox_audio_track->addItem(item.second, item.first);
		}
		ui.comboBox_audio_track->setCurrentIndex(ind);
		ui.comboBox_audio_track->blockSignals(false);
		ui.comboBox_audio_track->setEnabled(ind >= 0);

		// subtitle track
		ind = -1;
		track = VLCController::getInstance().getMediaSubtitleTrack();
		ui.comboBox_subtitle_track->blockSignals(true);
		ui.comboBox_subtitle_track->clear();
		for each (QPair<int, QString> item in VLCController::getInstance().getMediaSubtitleTracks())
		{
			if (track == item.first)
				ind = ui.comboBox_subtitle_track->count();

			ui.comboBox_subtitle_track->addItem(item.second, item.first);
		}
		ui.comboBox_subtitle_track->setCurrentIndex(ind);
		ui.comboBox_subtitle_track->blockSignals(false);
		ui.comboBox_subtitle_track->setEnabled(ind >= 0);

		// media total time
		ui.label_media_time_total->setText(VLCController::getInstance().getMediaTotalTime().toString());

		m_mediaInfoParsed = true;
	}

	// update media position
	ui.horizontalSlider_media_position->blockSignals(true);
	ui.horizontalSlider_media_position->setValue(position * (float)ui.horizontalSlider_media_position->maximum());
	ui.horizontalSlider_media_position->blockSignals(false);

	// update media time
	ui.label_media_time->setText(VLCController::getInstance().getMediaTime().toString());

	// update media volume & icon
	const int &vol = VLCController::getInstance().getMediaVolume();
	ui.horizontalSlider_media_volume->blockSignals(true);
	ui.horizontalSlider_media_volume->setValue(vol);
	ui.horizontalSlider_media_volume->blockSignals(false);
	ui.label_vol->setPixmap(QPixmap(vol > 0 ? ":/MediaPlayer/Resources/speaker.png" : ":/MediaPlayer/Resources/speaker_mute.png"));
}

void MediaPlayer::vlcError(QString error)
{
	QMessageBox::critical(this, this->windowTitle(), error, QMessageBox::Ok);
}

void MediaPlayer::on_pushButton_media_play_pause_clicked()
{
	// open if no media file
	if (!m_mediaFileReader)
	{
		// get media file
		QString mediaFilePath = QFileDialog::getOpenFileName(this, tr("Open Media File"));
		
		m_mediaFileReader = MediaFileFactory::createMediaFileReader(mediaFilePath);

		if (m_mediaFileReader->isSecureMedia())
		{
			static_cast<EncryptedMediaFileReader*>(m_mediaFileReader)->setMediaPasswordHash(
				CryptographyManager::SHA3_256(QInputDialog::getText(this, tr(MEDIA_FILE_EXTENSION), tr("Enter Media Password"), QLineEdit::Password))
			);
		}

		// try open the media file
		if (!m_mediaFileReader->open())
		{
			QMessageBox::critical(this, tr("Error"), tr("Media file couldn't be opened."));
			
			delete m_mediaFileReader;
			m_mediaFileReader = nullptr;
			return;
		}

		// init vlc wrapper
		VLCController::getInstance().init(m_mediaFileReader, ui.frame_video);
	}

	bool isPlaying = !VLCController::getInstance().isMediaPlaying();
	VLCController::getInstance().playPauseMedia(isPlaying);
}

void MediaPlayer::on_pushButton_media_stop_clicked()
{
	VLCController::getInstance().stopMedia();
}

void MediaPlayer::on_pushButton_media_repeat_clicked()
{
	// nop
}

void MediaPlayer::on_horizontalSlider_media_position_valueChanged(int value)
{
	QSlider *obj = ui.horizontalSlider_media_position;
	float new_value = value;

	// direct jump to the mouse click position on QSlider
	Qt::MouseButtons mb = QApplication::mouseButtons();
	QPoint pos = obj->mapFromGlobal(QCursor::pos());
	if ((mb & Qt::LeftButton) && (pos.x() >= 0 && pos.y() >= 0 && pos.x() < obj->size().width() && pos.y() < obj->size().height()))
	{
		new_value = (float)(obj->minimum() + (obj->maximum() - obj->minimum())) * pos.x() / (float)obj->size().width();
		if ((int)new_value != value)
		{
			obj->setValue((int)new_value);
			return;
		}
	}

	VLCController::getInstance().setMediaPosition(new_value / (float)obj->maximum());
}

void MediaPlayer::on_horizontalSlider_media_volume_valueChanged(int value)
{
	QSlider *obj = ui.horizontalSlider_media_volume;
	float new_value = value;

	// direct jump to the mouse click position on QSlider
	Qt::MouseButtons mb = QApplication::mouseButtons();
	QPoint pos = obj->mapFromGlobal(QCursor::pos());
	if ((mb & Qt::LeftButton) && (pos.x() >= 0 && pos.y() >= 0 && pos.x() < obj->size().width() && pos.y() < obj->size().height()))
	{
		new_value = (float)(obj->minimum() + (obj->maximum() - obj->minimum())) * pos.x() / (float)obj->size().width();
		if ((int)new_value != value)
		{
			obj->setValue((int)new_value);
			return;
		}
	}

	VLCController::getInstance().setMediaVolume((int)new_value);
}

void MediaPlayer::on_comboBox_video_track_currentIndexChanged(int index)
{
	VLCController::getInstance().setMediaVideoTrack(ui.comboBox_video_track->itemData(index).toInt());
}

void MediaPlayer::on_comboBox_audio_track_currentIndexChanged(int index)
{
	VLCController::getInstance().setMediaAudioTrack(ui.comboBox_audio_track->itemData(index).toInt());
}

void MediaPlayer::on_comboBox_subtitle_track_currentIndexChanged(int index)
{
	VLCController::getInstance().setMediaSubtitleTrack(ui.comboBox_subtitle_track->itemData(index).toInt());
}