

#include "crypto.h"
#include <openssl/evp.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <opensslpp/base64.h>
#include <opensslpp/aes_cbc.h>

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
		std::ifstream in_file(in_filename, std::ifstream::in);
		std::stringstream in_buffer;
		in_buffer << in_file.rdbuf();
		const std::vector<uint8_t> decoded = opensslpp::Base64::decode(in_buffer.str());
		std::string decoded_str(decoded.begin(), decoded.end());
		std::ofstream out_file(out_filename, std::ifstream::out);
		out_file << decoded_str;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: Could not decode " << in_filename << std::endl;
		return false;
	}
}



bool aes_cbc_create_key(const char* out_filename)
{
	try
	{
		auto newAes = opensslpp::Aes256Cbc::createNewKey();
		if (newAes == nullptr) throw;
		std::ofstream out_file(out_filename, std::ifstream::out);
		out_file << newAes->base64Key();
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: Could not generate key "<< std::endl;
		return false;
	}
}


bool aes_cbc_encode(
	const char* in_filename_data, 
	const char* in_filename_key, 
	const char* out_filename_data)
{
	try
	{
		std::ifstream in_file_data(in_filename_data, std::ifstream::in);
		std::stringstream in_buffer_data;
		in_buffer_data << in_file_data.rdbuf();

		std::ifstream in_file_key(in_filename_key, std::ifstream::in);
		std::stringstream in_buffer_key;
		in_buffer_key << in_file_key.rdbuf();
		
		auto aes = opensslpp::Aes256Cbc::createWithKey(in_buffer_key.str());

		if (aes == nullptr || aes->base64Key() != in_buffer_key.str()) throw;
		
		std::vector<uint8_t> cipher;

		if (!aes->encrypt(in_buffer_data.str(), cipher)) throw;

		std::ofstream out_file_data(out_filename_data, std::ios::out | std::ios::binary);
		out_file_data.write(reinterpret_cast<const char*>(cipher.data()), cipher.size());

		return true; 
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: Could not encode " << in_filename_data << std::endl;
		return false;
	}
}


bool aes_cbc_decode(
	const char* in_filename_data,
	const char* in_filename_key,
	const char* out_filename_data)
{
	try
	{
		std::vector<uint8_t> cipher;
		{
			std::ifstream in_file_data(in_filename_data, std::ios::in | std::ios::binary | std::ios::ate);
			auto fsize = in_file_data.tellg();
			in_file_data.seekg(0, std::ios::beg);
			cipher.resize(fsize);
			in_file_data.read(reinterpret_cast<char*>(&cipher[0]), fsize);
		}


		std::ifstream in_file_key(in_filename_key, std::ifstream::in);
		std::stringstream in_buffer_key;
		in_buffer_key << in_file_key.rdbuf();

		auto aes = opensslpp::Aes256Cbc::createWithKey(in_buffer_key.str());

		std::vector<uint8_t> decoded;
		if (!aes->decrypt(cipher, decoded)) throw("Exception: Failed decrypting");

		std::string decoded_str(decoded.begin(), decoded.end());
		std::ofstream out_file(out_filename_data, std::ifstream::out);
		out_file << decoded_str;
	}
	catch (const std::exception& e)
	{
		std::cout
			<< "Error: Could not decode " << in_filename_data << std::endl
			<< e.what() << std::endl;
		return false;
	}
}
