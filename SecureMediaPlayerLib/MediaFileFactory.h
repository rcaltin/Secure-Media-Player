/*
SecureMediaPlayerLib/MediaFileFactory.h

Author(s):
Recep ALTIN (rcaltin @ gmail . com) 10.02.2019
*/

#pragma once

#include <QString>
#include "EncryptedMediaFileReader.h"
#include "EncryptedMediaFileWriter.h"

namespace SecureMediaPlayerLib
{
	class MediaFileFactory
	{
	public:
		static MediaFileReader* createMediaFileReader(QString mediaFilePath);
		
		static MediaFileWriter* createMediaFileWriter(QString mediaFilePath);

	private:
		MediaFileFactory() = delete;
		~MediaFileFactory() = delete;
	};
}