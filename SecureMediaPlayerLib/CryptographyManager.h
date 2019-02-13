/*
SecureMediaPlayerLib/CryptographyManager.h

Author(s):
Recep ALTIN (rcaltin @ gmail . com) 10.02.2019
*/

#pragma once

#include <QString>
#include <mutex>

class SHA3;

namespace SecureMediaPlayerLib
{
	class CryptographyManager
	{
	public:
		~CryptographyManager();

		static std::string SHA3_256(std::string & plain);
		static QString SHA3_256(QString & plain);

		static void roll_SHA3_256(unsigned char * hash, int rollCount);

		static void AES_Encrypt(unsigned char * buffer, const unsigned char * key, const unsigned char * iv, int length = 64, int offset = 0);
		static void AES_Decrypt(unsigned char * buffer, const unsigned char * key, const unsigned char * iv, int length = 64, int offset = 0);

	private:
		CryptographyManager();
		
		static SHA3 sm_sha;
		static std::mutex sm_mutex;
	};
}