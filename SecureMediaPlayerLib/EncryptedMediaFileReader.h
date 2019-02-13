/*
SecureMediaPlayerLib/EncryptedMediaFileReader.h

Author(s):
Recep ALTIN (rcaltin @ gmail . com) 10.02.2019
*/

#pragma once

#include "MediaFileReader.h"

namespace SecureMediaPlayerLib
{
	class EncryptedMediaFileReader : public MediaFileReader
	{
		Q_OBJECT

	public:
		EncryptedMediaFileReader(QString mediaFilePath, QString mediaPasswordHash = QString(), QObject * parent = nullptr);
		~EncryptedMediaFileReader();
		EncryptedMediaFileReader(EncryptedMediaFileReader&) = delete;

		bool open() override;
		bool isSecureMedia() override;
		uint64_t readBlock(unsigned char * blockBuffer, uint64_t blockNum) override;
		uint64_t read(unsigned char * buffer, uint64_t length) override;

		void setMediaPasswordHash(const QString & mediaPasswordHash);

	private:
		void updateBlockKeyIV(const uint64_t block);

		unsigned char * m_mediaPasswordHash;
		unsigned char * m_tempBlockBuffer;
		unsigned char * m_lastKeyIV;
		uint64_t m_lastKeyIVBlock;
	};
}