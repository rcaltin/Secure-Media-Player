#include "MediaFileConverter.h"
#include <QThread>

using namespace SecureMediaPlayerLib;

MediaFileConverter::MediaFileConverter(MediaFileReader * mediaFileIn, MediaFileWriter * mediaFileOut, bool deleteFinished, QObject * parent)
	: QObject(parent), m_mediaFileIn(mediaFileIn), m_mediaFileOut(mediaFileOut), m_deleteFinished(deleteFinished)
{
}

void MediaFileConverter::process()
{
	emit mediaConversionStarted();

	bool succeedFlag = true;

	// try open input media
	if (!m_mediaFileIn->open())
	{
		emit mediaConversionError(tr("Input media could not opened."));
		succeedFlag = false;
	}

	// try open output media
	if (!m_mediaFileOut->open())
	{
		emit mediaConversionError(tr("Output media could not opened."));
		succeedFlag = false;
	}

	// start conversion
	if (succeedFlag)
	{
		uint64_t remainingBytes = m_mediaFileIn->mediaLength();
		unsigned char buffer[MEDIA_BLOCK_SIZE];

		for (uint64_t i = 0; i < m_mediaFileIn->mediaBlocksCount(); ++i)
		{
			m_mediaFileIn->readBlock(buffer, i);
			m_mediaFileOut->writeBlock(buffer);

			emit mediaConversionProgress((i + 1) * 100.0f / m_mediaFileIn->mediaBlocksCount());

			if (QThread::currentThread()->isInterruptionRequested())
			{
				succeedFlag = false;
				break;
			}
		}
	}

	m_mediaFileIn->close();
	m_mediaFileOut->close();

	emit mediaConversionFinished(succeedFlag);
	emit finished();
}

MediaFileConverter::~MediaFileConverter()
{
	if (m_deleteFinished)
	{
		if (m_mediaFileIn)
			delete m_mediaFileIn;

		if (m_mediaFileOut)
			delete m_mediaFileOut;

		m_mediaFileIn = nullptr;
		m_mediaFileOut = nullptr;
	}
}
