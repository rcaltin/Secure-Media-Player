/*
SecureMediaPlayerLib/MediaFileWriter.h

Author(s):
Recep ALTIN (rcaltin @ gmail . com) 10.02.2019
*/

#pragma once

#include <QObject>
#include <fstream>
#include "SecureMediaPlayerLibGlobals.h"

namespace SecureMediaPlayerLib
{
	class MediaFileWriter : public QObject
	{
		Q_OBJECT

	public:
		MediaFileWriter(QString mediaFilePath, QObject * parent = nullptr);
		virtual ~MediaFileWriter();
		MediaFileWriter(MediaFileWriter&) = delete;

		virtual bool open();
		virtual void close();
		virtual bool isSecureMedia();
		virtual uint64_t writeBlock(const unsigned char * blockBuffer);
	
	protected:
		QString m_mediaFilePath;
		std::fstream * m_mediaFileStream;
	};
}