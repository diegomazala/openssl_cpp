

#include <opensslpp/base64_dll.h>
#include <iostream>
#include <vector>

int main()
{
	{
		unsigned char data[] = "test";
		std::cout << sizeof(data) << std::endl;

		char* encoded_data;
		int encoded_length = 0;

		base64_encode((void*)data, sizeof(data), &encoded_data, encoded_length);

		unsigned char* decoded_data;
		int decoded_length = 0;

		base64_decode((void*)encoded_data, encoded_length, &decoded_data, decoded_length);

		std::cout << decoded_data << std::endl;
	}

	{
		std::vector<uint8_t> in_data_vec = { 0, 1, 2, 3, 4 };
		std::vector<uint8_t> out_data_vec = { 0, 0, 0, 0, 0 };


		char* encoded_data;
		int encoded_length = 0;

		base64_encode((void*)in_data_vec.data(), in_data_vec.size(), &encoded_data, encoded_length);


		unsigned char* decoded_data;
		int decoded_length = 0;

		base64_decode((void*)encoded_data, encoded_length, &decoded_data, decoded_length);

		std::memcpy(&out_data_vec[0], decoded_data, in_data_vec.size());

		for (auto c : in_data_vec) std::cout << (int)c << ' ';
		std::cout << std::endl;

		for (auto c : out_data_vec) std::cout << (int)c << ' ';
		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}
