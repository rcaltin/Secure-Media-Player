#include "EncryptedMediaFileReader.h"
#include "CryptographyManager.h"

using namespace SecureMediaPlayerLib;

EncryptedMediaFileReader::EncryptedMediaFileReader(QString mediaFilePath, QString mediaPasswordHash, QObject * parent)
	: MediaFileReader(mediaFilePath, parent), m_mediaPasswordHash(nullptr), m_lastKeyIV(nullptr)
{
	m_tempBlockBuffer = new unsigned char[MEDIA_BLOCK_SIZE];

	if (!mediaPasswordHash.isEmpty())
		setMediaPasswordHash(mediaPasswordHash);
}

EncryptedMediaFileReader::~EncryptedMediaFileReader()
{
	if (m_mediaPasswordHash)
		delete m_mediaPasswordHash;

	if (m_tempBlockBuffer)
		delete m_tempBlockBuffer;

	if (m_lastKeyIV)
		delete m_lastKeyIV;

	m_mediaPasswordHash = nullptr;
	m_tempBlockBuffer = nullptr;
	m_lastKeyIV = nullptr;
}

bool EncryptedMediaFileReader::open()
{
	if (MediaFileReader::open())
	{
		// num. of last block in the file
		int lastBlockNum = (m_mediaLength / MEDIA_BLOCK_SIZE) - 1;

		// read block from file to the temporal buffer
		m_mediaFileStream->seekg(lastBlockNum * MEDIA_BLOCK_SIZE);
		m_mediaFileStream->read((char *)m_tempBlockBuffer, MEDIA_BLOCK_SIZE);

		// update keys for the last block
		updateBlockKeyIV(lastBlockNum);

		// decrypt the last block
		CryptographyManager::AES_Decrypt(m_tempBlockBuffer, m_lastKeyIV, m_lastKeyIV + 32, MEDIA_BLOCK_SIZE);

		// find padding size of the last block
		int padding = MEDIA_BLOCK_PADDING_SIZE;
		for (; padding < MEDIA_BLOCK_SIZE; ++padding)
		{
			if (m_tempBlockBuffer[MEDIA_BLOCK_SIZE - padding] == MEDIA_BLOCK_PADDING_VALUE)
				continue;
			else if (m_tempBlockBuffer[MEDIA_BLOCK_SIZE - padding] == MEDIA_BLOCK_PADDING_TERMINATOR)
				break;

			// unusual block ending = corrupt file or password is wrong, so destroy it and return false
			m_mediaFileStream->close();
			delete m_mediaFileStream;
			m_mediaFileStream = nullptr;
			return false;
		}

		// remove all paddings from the total media length
		m_mediaLength -= (lastBlockNum * MEDIA_BLOCK_PADDING_SIZE) + padding;

		return true;
	}

	return false;
}

bool EncryptedMediaFileReader::isSecureMedia()
{
	return true;
}

uint64_t EncryptedMediaFileReader::readBlock(unsigned char * blockBuffer, uint64_t blockNum)
{
	// seek & read block from file to the buffer
	m_mediaFileStream->seekg(blockNum * MEDIA_BLOCK_SIZE);
	m_mediaFileStream->read((char*)blockBuffer, MEDIA_BLOCK_SIZE);

	// restore file seek
	m_mediaFileStream->seekg(m_seek);

	// update keys for the block
	updateBlockKeyIV(blockNum);

	// decrypt the block in the buffer
	CryptographyManager::AES_Decrypt(blockBuffer, m_lastKeyIV, m_lastKeyIV + 32, MEDIA_BLOCK_SIZE);

	// padding check
	int padding = MEDIA_BLOCK_PADDING_SIZE;
	if (blockBuffer[MEDIA_BLOCK_SIZE - MEDIA_BLOCK_PADDING_SIZE] != MEDIA_BLOCK_PADDING_TERMINATOR)
	{
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
	}

	return MEDIA_BLOCK_SIZE - padding;
}

uint64_t EncryptedMediaFileReader::read(unsigned char * buffer, uint64_t length)
{
	// eof check
	uint64_t readSize = length;
	if (m_seek + readSize > m_mediaLength)
	{
		if (!(readSize = m_mediaLength - m_seek))
			return 0;
	}

	// num. of first block for req. data
	int blockNum = m_seek / (MEDIA_BLOCK_SIZE - MEDIA_BLOCK_PADDING_SIZE);

	// offset over first block for req. data
	int blockOffset = m_seek % (MEDIA_BLOCK_SIZE - MEDIA_BLOCK_PADDING_SIZE);

	// count of encrypted blocks which need to be readed for req. data
	int blockCount =
		(readSize + blockOffset) / (MEDIA_BLOCK_SIZE - MEDIA_BLOCK_PADDING_SIZE) +
		((readSize + blockOffset) % (MEDIA_BLOCK_SIZE - MEDIA_BLOCK_PADDING_SIZE) ? 1 : 0);

	int bufferOffset = 0, copiedBytes = 0, remainingBytes = readSize;

	// iterate pending blocks
	do
	{
		// read block into temporal buffer
		if ((copiedBytes = (int)readBlock(m_tempBlockBuffer, blockNum++)) == 0)
			return -1;

		// copy from the temporal buffer to the actual buffer by -related part of- requested length
		memcpy(
			buffer + bufferOffset,
			m_tempBlockBuffer + blockOffset,
			copiedBytes = std::min(remainingBytes, copiedBytes - blockOffset)
		);

		// reset block-offset after first block is processed
		blockOffset = 0;

		// add copied-bytes to buffer-offset
		bufferOffset += copiedBytes;

		// subtract copied-bytes remaining-bytes
		remainingBytes -= copiedBytes;
	} while (--blockCount);

	// set new seek
	m_seek += readSize;

	return readSize;
}

void EncryptedMediaFileReader::setMediaPasswordHash(const QString & mediaPasswordHash)
{
	if (!mediaPasswordHash.isEmpty())
	{
		if (!m_mediaPasswordHash)
			m_mediaPasswordHash = new unsigned char[256];
		memcpy(m_mediaPasswordHash, mediaPasswordHash.toStdString().c_str(), 256);

		if (!m_lastKeyIV)
			m_lastKeyIV = new unsigned char[64];
		memcpy(m_lastKeyIV, m_mediaPasswordHash, 64);
	}
}

void EncryptedMediaFileReader::updateBlockKeyIV(const uint64_t block)
{
	// return if block = last block OR media has no password
	if (block == m_lastKeyIVBlock || !m_lastKeyIV || !m_mediaPasswordHash)
		return;

	// rewind check
	if (block < m_lastKeyIVBlock || m_lastKeyIVBlock < 0)
	{
		// reset to the start point
		memcpy(m_lastKeyIV, m_mediaPasswordHash, 64);
		m_lastKeyIVBlock = 0;
	}

	// roll for the block
	CryptographyManager::roll_SHA3_256(m_lastKeyIV, block - m_lastKeyIVBlock);

	// update last block
	m_lastKeyIVBlock = block;
}