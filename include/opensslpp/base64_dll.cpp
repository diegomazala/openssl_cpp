

#include "base64_dll.h"
#include <openssl/evp.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <opensslpp/base64.h>

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


bool base64_encode_text_file(const char* in_filename, const char* out_filename)
{
	try
	{
		std::ifstream in_file(in_filename, std::ifstream::in);
		std::stringstream in_buffer;
		in_buffer << in_file.rdbuf();
		std::vector<uint8_t> decoded_str;
		std::copy(std::istream_iterator<uint8_t>(in_buffer), std::istream_iterator<uint8_t>(), std::back_inserter(decoded_str));
		const std::string encoded = opensslpp::Base64::encode(decoded_str);
		std::ofstream out_file(out_filename, std::ifstream::out);
		out_file << encoded;
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: Could not encode " << in_filename << std::endl;
		return false;
	}
}


bool base64_decode_text_file(const char* in_filename, const char* out_filename)
{
	try
	{
		std::ifstream in_file(in_filename, std::ifstream::out);
		std::stringstream in_buffer;
		in_buffer << in_file.rdbuf();
		const std::vector<uint8_t> decoded = opensslpp::Base64::decode(in_buffer.str());

		std::string decoded_str(decoded.begin(), decoded.end());

		std::cout << decoded_str << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: Could not decode " << in_filename << std::endl;
		return false;
	}
}
