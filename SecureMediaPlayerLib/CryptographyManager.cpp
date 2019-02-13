#include "CryptographyManager.h"
#include "sha3.h"
#include "aes.hpp"

using namespace SecureMediaPlayerLib;

SHA3 CryptographyManager::sm_sha(SHA3::Bits256);
std::mutex CryptographyManager::sm_mutex;

CryptographyManager::CryptographyManager()
{
}

CryptographyManager::~CryptographyManager()
{
}

std::string CryptographyManager::SHA3_256(std::string & plain)
{
	std::lock_guard<std::mutex> lock(sm_mutex);

	return sm_sha(plain);
}

QString CryptographyManager::SHA3_256(QString & plain)
{
	return QString::fromStdString(SHA3_256(plain.toStdString()));
}

void CryptographyManager::roll_SHA3_256(unsigned char * hash, int rollCount)
{
	std::lock_guard<std::mutex> lock(sm_mutex);

	while (rollCount-- > 0)
		memcpy(hash, sm_sha(hash, 64).c_str(), 64);
}

void CryptographyManager::AES_Encrypt(unsigned char * buffer, const unsigned char * key, const unsigned char * iv, int length, int offset)
{
	std::lock_guard<std::mutex> lock(sm_mutex);

	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_encrypt_buffer(&ctx, buffer + offset, length);
}

void CryptographyManager::AES_Decrypt(unsigned char * buffer, const unsigned char * key, const unsigned char * iv, int length, int offset)
{
	std::lock_guard<std::mutex> lock(sm_mutex);

	struct AES_ctx ctx;
	AES_init_ctx_iv(&ctx, key, iv);
	AES_CBC_decrypt_buffer(&ctx, buffer + offset, length);
}
