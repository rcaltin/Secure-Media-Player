#include "MediaFileReader.h"

using namespace SecureMediaPlayerLib;

MediaFileReader::MediaFileReader(QString mediaFilePath, QObject * parent)
	: QObject(parent),
	m_mediaFilePath(mediaFilePath),
	m_mediaFileStream(nullptr),
	m_seek(0)
{
}

MediaFileReader::~MediaFileReader()
{
	close();
}

bool MediaFileReader::open()
{
	m_seek = 0;
	m_mediaFileStream = new std::fstream(m_mediaFilePath.toStdString().c_str(), std::fstream::in | std::fstream::binary);

	if (m_mediaFileStream->is_open())
	{
		// read the media length
		m_mediaFileStream->seekg(0, m_mediaFileStream->end);
		m_mediaLength = m_mediaFileStream->tellg();

		m_mediaFileStream->seekg(0);
		return true;
	}

	delete m_mediaFileStream;
	m_mediaFileStream = nullptr;
	return false;
}
void MediaFileReader::close()
{
	if (m_mediaFileStream)
	{
		m_mediaFileStream->close();
		delete m_mediaFileStream;
	}

	m_mediaFileStream = nullptr;
}

bool MediaFileReader::isSecureMedia()
{
	return false;
}

uint64_t MediaFileReader::readBlock(unsigned char * buffer, uint64_t blockNum)
{
	// eof check
	uint64_t readSize = MEDIA_BLOCK_SIZE - MEDIA_BLOCK_PADDING_SIZE;
	uint64_t blockAddr = blockNum * (MEDIA_BLOCK_SIZE - MEDIA_BLOCK_PADDING_SIZE);
	if (blockAddr + readSize > m_mediaLength)
	{
		if (!(readSize = m_mediaLength - blockAddr))
			return 0;
	}

	// seek & read block from file to the temporal buffer
	m_mediaFileStream->seekg(blockAddr);
	m_mediaFileStream->read((char *)buffer, readSize);

	// restore file seek
	m_mediaFileStream->seekg(m_seek);

	// fill the buffer with the padding value
	std::fill(buffer + readSize, buffer + MEDIA_BLOCK_SIZE, MEDIA_BLOCK_PADDING_VALUE);

	// put the padding terminator
	buffer[readSize] = MEDIA_BLOCK_PADDING_TERMINATOR;
	
	return readSize;
}

uint64_t MediaFileReader::mediaBlocksCount()
{
	return m_mediaLength / (MEDIA_BLOCK_SIZE - MEDIA_BLOCK_PADDING_SIZE);
}

uint64_t MediaFileReader::mediaLength()
{
	return m_mediaLength;
}

void MediaFileReader::seek(uint64_t seek)
{
	m_seek = seek;
}

uint64_t MediaFileReader::read(unsigned char * buffer, uint64_t length)
{
	// eof check
	uint64_t readSize = length;
	if (m_seek + readSize > m_mediaLength)
	{
		if (!(readSize = m_mediaLength - m_seek))
			return 0;
	}

	// seek & read by length
	m_mediaFileStream->seekg(m_seek);
	m_mediaFileStream->read((char *)buffer, readSize);

	// set new seek
	m_seek += readSize;

	return readSize;
}