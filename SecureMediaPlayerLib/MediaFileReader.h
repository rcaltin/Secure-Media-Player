/*
SecureMediaPlayerLib/MediaFileReader.h

Author(s):
Recep ALTIN (rcaltin @ gmail . com) 10.02.2019
*/

#pragma once

#include <QObject>
#include <fstream>
#include "SecureMediaPlayerLibGlobals.h"

namespace SecureMediaPlayerLib
{
	class MediaFileReader : public QObject
	{
		Q_OBJECT

	public:
		MediaFileReader(QString mediaFilePath, QObject * parent = nullptr);
		virtual ~MediaFileReader();
		MediaFileReader(MediaFileReader&) = delete;

		virtual bool open();
		virtual void close();
		virtual bool isSecureMedia();
		virtual uint64_t readBlock(unsigned char *buffer, uint64_t blockNum);
		
		uint64_t mediaBlocksCount();
		uint64_t mediaLength();
		void seek(uint64_t seek);
		virtual uint64_t read(unsigned char *buffer, uint64_t length);

	protected:
		QString m_mediaFilePath;
		std::fstream * m_mediaFileStream;
		uint64_t m_mediaLength;
		uint64_t m_seek;
	};
}