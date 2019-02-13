#include "EncryptedMediaFileWriter.h"
#include "CryptographyManager.h"

using namespace SecureMediaPlayerLib;

EncryptedMediaFileWriter::EncryptedMediaFileWriter(QString mediaFilePath, QString mediaPasswordHash, QObject * parent)
	: MediaFileWriter(mediaFilePath, parent), m_mediaPasswordHash(nullptr), m_lastKeyIV(nullptr)
{
	m_tempBlockBuffer = new unsigned char[MEDIA_BLOCK_SIZE];

	if (!mediaPasswordHash.isEmpty())
		setMediaPasswordHash(mediaPasswordHash);
}

EncryptedMediaFileWriter::~EncryptedMediaFileWriter()
{
	if (m_mediaPasswordHash)
		delete m_mediaPasswordHash;

	if (m_tempBlockBuffer)
		delete m_tempBlockBuffer;

	if (m_lastKeyIV)
		delete m_lastKeyIV;

	m_mediaPasswordHash = nullptr;
	m_lastKeyIV = nullptr;
}

bool EncryptedMediaFileWriter::isSecureMedia()
{
	return true;
}

uint64_t EncryptedMediaFileWriter::writeBlock(const unsigned char * blockBuffer)
{
	// copy block to the temporal buffer
	memcpy(m_tempBlockBuffer, blockBuffer, MEDIA_BLOCK_SIZE);

	// encrypt the temporal buffer
	CryptographyManager::AES_Encrypt(m_tempBlockBuffer, m_lastKeyIV, m_lastKeyIV + 32, MEDIA_BLOCK_SIZE);

	// roll the key for the next block
	CryptographyManager::roll_SHA3_256(m_lastKeyIV, 1);

	// write temporal block to the file
	m_mediaFileStream->write((char *)m_tempBlockBuffer, MEDIA_BLOCK_SIZE);

	return MEDIA_BLOCK_SIZE;
}

void EncryptedMediaFileWriter::setMediaPasswordHash(const QString & mediaPasswordHash)
{
	if (!mediaPasswordHash.isEmpty())
	{
		if(!m_mediaPasswordHash)
			m_mediaPasswordHash = new unsigned char[256];
		memcpy(m_mediaPasswordHash, mediaPasswordHash.toStdString().c_str(), 256);

		if(!m_lastKeyIV)
			m_lastKeyIV = new unsigned char[64];
		memcpy(m_lastKeyIV, m_mediaPasswordHash, 64);
	}
}
