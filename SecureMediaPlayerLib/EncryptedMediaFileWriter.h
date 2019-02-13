/*
SecureMediaPlayerLib/EncryptedMediaFileWriter.h

Author(s):
Recep ALTIN (rcaltin @ gmail . com) 10.02.2019
*/

#pragma once

#include "MediaFileWriter.h"

namespace SecureMediaPlayerLib
{
	class EncryptedMediaFileWriter : public MediaFileWriter
	{
		Q_OBJECT

	public:
		EncryptedMediaFileWriter(QString mediaFilePath, QString mediaPasswordHash = QString(), QObject * parent = nullptr);
		~EncryptedMediaFileWriter();
		EncryptedMediaFileWriter(EncryptedMediaFileWriter&) = delete;

		bool isSecureMedia() override;
		uint64_t writeBlock(const unsigned char * blockBuffer) override;

		void setMediaPasswordHash(const QString & mediaPasswordHash);

	private:
		unsigned char * m_mediaPasswordHash;
		unsigned char * m_tempBlockBuffer;
		unsigned char * m_lastKeyIV;
	};
}