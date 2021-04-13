

#include <opensslpp/crypto.h>
#include <opensslpp/aes_cbc.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

int main()
{

	{
		const char* input_data_filename = "c:/tmp/crypto/template.json";
		const char* aes_key_filename = "c:/tmp/crypto/aes.key";
		const char* aes_enc_filename = "c:/tmp/crypto/aes.enc";
		const char* aes_dec_filename = "c:/tmp/crypto/aes_out.json";

		std::cout << "##################### AES_CBC_256 To/From File ##################" << std::endl;
		//{
		//	std::cout << "Creating key ..." << std::endl;
		//	aes_cbc_create_key(aes_key_filename);
		//}
		{
			std::cout << "Encoding ..." << std::endl;
			aes_cbc_encode_to_file(
				input_data_filename,
				aes_key_filename,
				aes_enc_filename);
		}
		{
			std::cout << "Decoding ..." << std::endl;
			aes_cbc_decode_to_file(
				aes_enc_filename,
				aes_key_filename,
				aes_dec_filename);

			char data[256];
			int length = aes_cbc_decode_to_str(
				aes_enc_filename,
				aes_key_filename,
				data);
			std::cout << length << std::endl << data << std::endl;
		}

		{
			std::cout << "Checking data ..." << std::endl;

			std::vector<uint8_t> in_data;
			{
				std::ifstream in_file_data(input_data_filename, std::ifstream::in | std::ifstream::binary);
				in_file_data.seekg (0, in_file_data.end);
				int length = in_file_data.tellg();
				in_file_data.seekg (0, in_file_data.beg);
				in_data.resize(length);
				in_file_data.read(reinterpret_cast<char*>(in_data.data()), length);
				in_file_data.close();
			}

			std::vector<uint8_t> dec_data;
			{
				std::ifstream dec_file_data(aes_dec_filename, std::ifstream::in | std::ifstream::binary);
				dec_file_data.seekg (0, dec_file_data.end);
				int length = dec_file_data.tellg();
				dec_file_data.seekg (0, dec_file_data.beg);
				dec_data.resize(length);
				dec_file_data.read(reinterpret_cast<char*>(dec_data.data()), length);
				dec_file_data.close();
			}


			if (std::string(in_data.begin(), in_data.end()) == std::string(dec_data.begin(), dec_data.end()))
			{
				std::cout << "Success: Input and output file content are equal" << std::endl;
			}
			else
			{
				std::cout << "Fail: Input and output file content are different" << std::endl;
			}
		}

		std::cout << "#################################################################" << std::endl;
	}
	return 0;

	{
		std::cout << "############### Base64 Encode/Decode To/From File ##############" << std::endl;
		base64_encode_text_file("c:/tmp/crypto/template.txt", "c:/tmp/crypto/out_encoded.txt");
		base64_decode_text_file("c:/tmp/crypto/out_encoded.txt", "c:/tmp/crypto/out_decoded.txt");
		std::cout << "#################################################################" << std::endl;
	}

	{
		std::cout << "############### Base64 Encode/Decode char* ######################" << std::endl;

		unsigned char data[] = "hello world";

		char* encoded_data;
		int encoded_length = 0;

		base64_encode((void*)data, sizeof(data), &encoded_data, encoded_length);

		unsigned char* decoded_data;
		int decoded_length = 0;

		base64_decode((void*)encoded_data, encoded_length, &decoded_data, decoded_length);

		std::cout << "decoded: " << decoded_data << std::endl;
		std::cout << "#################################################################" << std::endl;
	}


	return EXIT_SUCCESS;
}
