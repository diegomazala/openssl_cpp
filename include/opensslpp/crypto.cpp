

#include "crypto.h"
#include <openssl/evp.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <opensslpp/base64.h>
#include <opensslpp/aes_cbc.h>


void base64_encode(const void* in_data, int in_length, char** out_data, int& out_length)
{
	const auto pl = 4 * ((in_length + 2) / 3);
	*out_data = reinterpret_cast<char*>(calloc(pl + 1, 1)); //+1 for the terminating null that EVP_EncodeBlock adds on
	out_length = EVP_EncodeBlock(reinterpret_cast<unsigned char*>(*out_data), reinterpret_cast<const unsigned char*>(in_data), in_length);
}


void base64_decode(const void* in_data, int in_length, unsigned char** out_data, int& out_length)
{
	const auto pl = 3 * in_length / 4;
	*out_data = reinterpret_cast<unsigned char*>(calloc(pl + 1, 1));
	out_length = EVP_DecodeBlock(*out_data, reinterpret_cast<const unsigned char*>(in_data), in_length);
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
		std::ofstream out_file(out_filename, std::ifstream::out | std::ios::binary);
		out_file.write(reinterpret_cast<const char*>(newAes->key().data()), newAes->key().size());
		out_file.close();
		return true;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: Could not generate key "<< std::endl;
		return false;
	}
}


bool aes_cbc_encode_to_file(
	const char* in_filename_data, 
	const char* in_filename_key, 
	const char* out_filename_data)
{
	try
	{
		std::vector<uint8_t> in_data;
		{
			std::ifstream in_file_data(in_filename_data, std::ifstream::in | std::ifstream::binary);
			in_file_data.seekg (0, in_file_data.end);
			int length = in_file_data.tellg();
			in_file_data.seekg (0, in_file_data.beg);
			in_data.resize(length);
			in_file_data.read(reinterpret_cast<char*>(&in_data[0]), length);
			in_file_data.close();
		}

		opensslpp::Aes256Cbc::Key key;
		{
			std::ifstream in_file_key(in_filename_key, std::ifstream::in | std::ifstream::binary);
			in_file_key.seekg (0, in_file_key.end);
			int length = in_file_key.tellg();
			in_file_key.seekg (0, in_file_key.beg);

			char* buffer = new char[length];
			in_file_key.read(buffer, length);
			in_file_key.close();

			std::memcpy(key.data(), buffer, length);

			delete[] buffer;
		}
		auto aes = opensslpp::Aes256Cbc::createWithKey(key);

		
		std::vector<uint8_t> cipher;
		if (!aes->encrypt(in_data.data(), in_data.size(), cipher)) throw;

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


bool aes_cbc_decode_to_file(
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

		opensslpp::Aes256Cbc::Key key;
		std::ifstream in_file_key(in_filename_key, std::ifstream::in | std::ifstream::binary);
		in_file_key.seekg (0, in_file_key.end);
		int length = in_file_key.tellg();
		in_file_key.seekg (0, in_file_key.beg);

		char* buffer = new char[length];
		in_file_key.read(buffer, length);
		in_file_key.close();

		std::memcpy(key.data(), buffer, length);
		auto aes = opensslpp::Aes256Cbc::createWithKey(key);
		delete[] buffer;

		std::vector<uint8_t> decoded;
		if (!aes->decrypt(cipher, decoded)) throw("Exception: Failed decrypting");

		std::ofstream out_file_data(out_filename_data, std::ios::out | std::ios::binary);
		out_file_data.write(reinterpret_cast<const char*>(decoded.data()), decoded.size());

	}
	catch (const std::exception& e)
	{
		std::cout
			<< "Error: Could not decode " << in_filename_data << std::endl
			<< e.what() << std::endl;
		return false;
	}
}



int aes_cbc_decode_to_str(
	const char* in_filename_data,
	const char* in_filename_key,
	char* out_decoded_data)
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

		opensslpp::Aes256Cbc::Key key;
		std::ifstream in_file_key(in_filename_key, std::ifstream::in | std::ifstream::binary);
		in_file_key.seekg (0, in_file_key.end);
		int length = in_file_key.tellg();
		in_file_key.seekg (0, in_file_key.beg);

		char* buffer = new char[length];
		in_file_key.read(buffer, length);
		in_file_key.close();

		std::memcpy(key.data(), buffer, length);
		auto aes = opensslpp::Aes256Cbc::createWithKey(key);
		delete[] buffer;

		std::vector<uint8_t> decoded;
		if (!aes->decrypt(cipher, decoded)) throw("Exception: Failed decrypting");

		decoded.push_back('\0');
		memcpy(out_decoded_data, decoded.data(), decoded.size());
		return decoded.size();
	}
	catch (const std::exception& e)
	{
		std::cout
			<< "Error: Could not decode " << in_filename_data << std::endl
			<< e.what() << std::endl;
		return 0;
	}
}
