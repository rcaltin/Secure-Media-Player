#include "MediaFileWriter.h"

using namespace SecureMediaPlayerLib;

MediaFileWriter::MediaFileWriter(QString mediaFilePath, QObject * parent)
	: QObject(parent),
	m_mediaFilePath(mediaFilePath)
{
}

MediaFileWriter::~MediaFileWriter()
{
	close();
}

bool MediaFileWriter::open()
{
	m_mediaFileStream = new std::fstream(m_mediaFilePath.toStdString().c_str(), std::fstream::out | std::fstream::binary);
	
	if (m_mediaFileStream->is_open())
		return true;

	delete m_mediaFileStream;
	m_mediaFileStream = nullptr;
	return false;
}

void MediaFileWriter::close()
{
	if (m_mediaFileStream)
	{
		m_mediaFileStream->close();
		delete m_mediaFileStream;
	}

	m_mediaFileStream = nullptr;
}

bool MediaFileWriter::isSecureMedia()
{
	return false;
}

uint64_t MediaFileWriter::writeBlock(const unsigned char * blockBuffer)
{
	int padding = MEDIA_BLOCK_PADDING_SIZE;

	// find padding size in the last block of the file
	for (; padding < MEDIA_BLOCK_SIZE; ++padding)
	{
		if (blockBuffer[MEDIA_BLOCK_SIZE - padding] == MEDIA_BLOCK_PADDING_VALUE)
			continue;
		else if (blockBuffer[MEDIA_BLOCK_SIZE - padding] == MEDIA_BLOCK_PADDING_TERMINATOR)
			break;

		//  unusual block ending = corrupt file or password is wrong,
		return 0;
	}

	// write block to the file
	m_mediaFileStream->write((char *)blockBuffer, MEDIA_BLOCK_SIZE - padding);

	return MEDIA_BLOCK_SIZE - padding;
}
