#include "MediaFileFactory.h"

using namespace SecureMediaPlayerLib;

MediaFileReader* MediaFileFactory::createMediaFileReader(QString mediaFilePath)
{
	if (mediaFilePath.endsWith(MEDIA_FILE_EXTENSION))
		return new EncryptedMediaFileReader(mediaFilePath);

	return new MediaFileReader(mediaFilePath);
}

MediaFileWriter* MediaFileFactory::createMediaFileWriter(QString mediaFilePath)
{
	if (mediaFilePath.endsWith(MEDIA_FILE_EXTENSION))
		return new EncryptedMediaFileWriter(mediaFilePath);

	return new MediaFileWriter(mediaFilePath);
}
