

#include "base64_dll.h"
#include <openssl/evp.h>

void base64_encode(const void* in_data, int in_length, char** out_data, int& out_length)
{
	const auto pl = 4 * ((in_length + 2) / 3);
	*out_data = reinterpret_cast<char*>(calloc(pl + 1, 1)); //+1 for the terminating null that EVP_EncodeBlock adds on
	out_length = EVP_EncodeBlock(reinterpret_cast<unsigned char*>(*out_data), reinterpret_cast<const unsigned char*>(in_data), in_length);
	//if (pl != out_length) { std::cerr << "Whoops, encode predicted " << pl << " but we got " << out_length << "\n"; }
}

void base64_decode(const void* in_data, int in_length, unsigned char** out_data, int& out_length)
{
	const auto pl = 3 * in_length / 4;
	*out_data = reinterpret_cast<unsigned char*>(calloc(pl + 1, 1));
	out_length = EVP_DecodeBlock(*out_data, reinterpret_cast<const unsigned char*>(in_data), in_length);
	//if (pl != out_length) { std::cerr << "Whoops, decode predicted " << pl << " but we got " << out_length << "\n"; }
}
