/*
SecureMediaPlayerLib/SecureMediaPlayerLib.h

Author(s):
Recep ALTIN (rcaltin @ gmail . com) 10.02.2019
*/

#pragma once

#include <stdint.h>

namespace SecureMediaPlayerLib
{
	//	Media Block Size in the file, must be N * 16Byte! 
	//	libVLC usually asks 16KB for its buffering requests, 
	//	so plus over 16B(min. AES-128 block size) to tolerating padding size(=2?) would be better to process a request with less encryption time loss
	constexpr uint64_t			MEDIA_BLOCK_SIZE				= 16384 + 16;

	//	padding size for a fully filled media block,
	//	must be >=2, 1Byte for the MEDIA_BLOCK_PADDING_DELIMITER and 1+NByte for the MEDIA_BLOCK_PADDING_VALUE
	constexpr uint64_t			MEDIA_BLOCK_PADDING_SIZE		= 2;

	//	ISO/IEC 7816-4 => 0x10000000 as padding terminator
	constexpr unsigned char		MEDIA_BLOCK_PADDING_TERMINATOR	= 0x80;

	//	ISO/IEC 7816-4 => 0x00000000 as padding value
	constexpr unsigned char		MEDIA_BLOCK_PADDING_VALUE		= 0x00;

	// encrypted media file extension
	constexpr auto				MEDIA_FILE_EXTENSION			= ".smpf";
}