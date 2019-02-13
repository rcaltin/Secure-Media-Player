/*
SecureMediaPlayerLib/MediaFileConverter.h

Author(s):
Recep ALTIN (rcaltin @ gmail . com) 10.02.2019
*/

#pragma once

#include <QObject>
#include "EncryptedMediaFileReader.h"
#include "EncryptedMediaFileWriter.h"

namespace SecureMediaPlayerLib
{
	class MediaFileConverter : public QObject
	{
		Q_OBJECT

	public:
		MediaFileConverter(MediaFileReader * mediaFileIn, MediaFileWriter * mediaFileOut, bool deleteFinished = false, QObject * parent = nullptr);
		~MediaFileConverter();

	public slots:
		void process();

	signals:
		void mediaConversionStarted();
		void mediaConversionProgress(float percent);
		void mediaConversionFinished(bool successful = true);
		void mediaConversionError(QString errorMessage);
		void finished();

	private:
		MediaFileReader * m_mediaFileIn;
		MediaFileWriter * m_mediaFileOut;
		bool m_deleteFinished;
	};
}