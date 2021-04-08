

#include <opensslpp/crypto.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

int main()
{
	{
		const char* input_data_filename = "c:/tmp/crypto/template.txt";
		const char* aes_key_filename = "c:/tmp/crypto/aes_key.txt";
		const char* aes_iv_filename = "c:/tmp/crypto/aes_iv.bin";
		const char* aes_enc_filename = "c:/tmp/crypto/aes_enc.bin";
		const char* aes_dec_filename = "c:/tmp/crypto/aes_dec.txt";

		std::cout << "##################### AES_CBC_256 To/From File ##################" << std::endl;
		{
			std::cout << "Creating key ..." << std::endl;
			aes_cbc_create_key(aes_key_filename);
		}
		{
			std::cout << "Encoding ..." << std::endl;
			aes_cbc_encode(
				input_data_filename,
				aes_key_filename,
				aes_enc_filename,
				aes_iv_filename);
		}
		{
			std::cout << "Decoding ..." << std::endl;
			aes_cbc_decode(
				aes_enc_filename,
				aes_key_filename,
				aes_iv_filename,
				aes_dec_filename);
		}
		{
			std::cout << "Checking data ..." << std::endl;
			std::ifstream in_file_data(input_data_filename, std::ifstream::in);
			std::stringstream in_buffer_data;
			in_buffer_data << in_file_data.rdbuf();

			std::ifstream dec_file_data(aes_dec_filename, std::ifstream::in);
			std::stringstream dec_buffer_data;
			dec_buffer_data << dec_file_data.rdbuf();

			if (in_buffer_data.str() == dec_buffer_data.str())
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
