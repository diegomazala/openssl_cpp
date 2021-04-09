
#include <opensslpp/base64.h>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>

#if 0

#include <stdio.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <stdint.h>

#define OP_ENCODE 0
#define OP_DECODE 1

int b64_op(const char* in, int in_len,
	char* out, int out_len, int op)
{
	int ret = 0;
	BIO* b64 = BIO_new(BIO_f_base64());
	BIO* bio = BIO_new(BIO_s_mem());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	BIO_push(b64, bio);
	if (op == 0)
	{
		ret = BIO_write(b64, in, in_len);
		BIO_flush(b64);
		if (ret > 0)
		{
			ret = BIO_read(bio, out, out_len);
		}

	}
	else
	{
		ret = BIO_write(bio, in, in_len);
		BIO_flush(bio);
		if (ret)
		{
			ret = BIO_read(b64, out, out_len);
		}
	}
	BIO_free(b64); // MEMORY LEAK HERE? 
	return ret;
}

int main(void)
{
	std::string data_in = "hello world";
	char enc_data[] = "grrr shebangit!";
	char out[256];
	//char* out;
	char orig[256];

	int enc_out_len =
		b64_op(enc_data, sizeof(enc_data) - 1,
			out, sizeof(out), OP_ENCODE);

	printf("Enc data [%s] len [%d]\n",
		out, enc_out_len);

	int dec_out_len =
		b64_op(out, enc_out_len,
			orig, sizeof(orig), OP_DECODE);

	printf("Dec data [%s] len [%d]\n",
		orig, dec_out_len);

	return 0;
}

#endif



#if 1

int main()
{
    const std::vector<uint8_t> data = { 1, 2, 3, 4, 5, 6 };


	{
		auto encoder = opensslpp::makeBio(BIO_f_base64());
		auto buffer_enc = opensslpp::makeBio(BIO_s_mem());
		auto stream_enc = BIO_push(encoder.get(), buffer_enc.get());

		if (!stream_enc)
		{
			std::cerr << "Error\n";
			return 0;
		}

		BIO_set_flags(stream_enc, BIO_FLAGS_BASE64_NO_NL);
		BIO_write(stream_enc, data.data(), static_cast<int>(data.size()));
		BIO_flush(stream_enc);

		BUF_MEM* ptr = nullptr;
		BIO_get_mem_ptr(stream_enc, &ptr);

		std::cout << ptr->length << " " << ptr->max << std::endl;


		opensslpp::BioMemPtr buffer_dec = opensslpp::makeBio(BIO_new_mem_buf(ptr->data, ptr->length));
		opensslpp::BioMemPtr decoder = opensslpp::makeBio(BIO_f_base64());
		BIO* stream_dec = BIO_push(decoder.get(), buffer_dec.get());

		if (!stream_dec)
			return 0;

		//BIO_set_flags(stream_dec, BIO_FLAGS_BASE64_NO_NL);
		//auto ret = BIO_read(stream_dec, data, static_cast<int>(size));
		//std::cout << ret << std::endl;
	}



	//return 0;

    {
        const auto encoded = opensslpp::Base64::encode(data);
        const auto decoded = opensslpp::Base64::decode(encoded);

        assert(data == decoded);

        std::cout << "data   : ";
		for (auto v : data) std::cout << v;
		std::cout << std::endl;

		std::cout << "encoded: ";
		for (auto v : encoded) std::cout << v;
		std::cout << std::endl;

		std::cout << "decoded: ";
		for (auto v : decoded) std::cout << v;
		std::cout << std::endl;
    }

    {
        std::vector<uint8_t> decoded(data.size());
		std::vector<uint8_t> encoded_data;

        const auto encoded = opensslpp::Base64::encode(data.data(), data.size());
		const auto encoded_test_size = opensslpp::Base64::encode(encoded_data, data.data(), data.size());
        //const auto size = opensslpp::Base64::decode(encoded, decoded.data(), decoded.size());
		const auto size = opensslpp::Base64::decode(encoded_data, decoded.data(), decoded.size());

        assert(size == decoded.size());
        assert(data == decoded);

		std::cout << "decoded: ";
		for (auto v : decoded) std::cout << v;
		std::cout << std::endl;

		std::cout << "encoded: ";
		for (auto v : encoded) std::cout << v;
		std::cout << std::endl;

		std::cout << "size   : " << size << std::endl;
    }

    return EXIT_SUCCESS;
}

#endif


#if 0

#include <iostream>
#include <stdlib.h>
#include <openssl/evp.h>

char* base64(const unsigned char* input, int length) {
	const auto pl = 4 * ((length + 2) / 3);
	auto output = reinterpret_cast<char*>(calloc(pl + 1, 1)); //+1 for the terminating null that EVP_EncodeBlock adds on
	const auto ol = EVP_EncodeBlock(reinterpret_cast<unsigned char*>(output), input, length);
	if (pl != ol) { std::cerr << "Whoops, encode predicted " << pl << " but we got " << ol << "\n"; }
	return output;
}

unsigned char* decode64(const char* input, int length) {
	const auto pl = 3 * length / 4;
	auto output = reinterpret_cast<unsigned char*>(calloc(pl + 1, 1));
	const auto ol = EVP_DecodeBlock(output, reinterpret_cast<const unsigned char*>(input), length);
	if (pl != ol) { std::cerr << "Whoops, decode predicted " << pl << " but we got " << ol << "\n"; }
	return output;
}

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include <iostream>

namespace {
	struct BIOFreeAll { void operator()(BIO* p) { BIO_free_all(p); } };
}

std::string Base64Encode(const std::vector<unsigned char>& binary)
{
	std::unique_ptr<BIO, BIOFreeAll> b64(BIO_new(BIO_f_base64()));
	BIO_set_flags(b64.get(), BIO_FLAGS_BASE64_NO_NL);
	BIO* sink = BIO_new(BIO_s_mem());
	BIO_push(b64.get(), sink);
	BIO_write(b64.get(), binary.data(), binary.size());
	BIO_flush(b64.get());
	const char* encoded;
	const long len = BIO_get_mem_data(sink, &encoded);
	return std::string(encoded, len);
}

// Assumes no newlines or extra characters in encoded string
std::vector<unsigned char> Base64Decode(const char* encoded)
{
	std::unique_ptr<BIO, BIOFreeAll> b64(BIO_new(BIO_f_base64()));
	BIO_set_flags(b64.get(), BIO_FLAGS_BASE64_NO_NL);
	BIO* source = BIO_new_mem_buf(encoded, -1); // read-only source
	BIO_push(b64.get(), source);
	const int maxlen = strlen(encoded) / 4 * 3 + 1;
	std::vector<unsigned char> decoded(maxlen);
	const int len = BIO_read(b64.get(), decoded.data(), maxlen);
	decoded.resize(len);
	return decoded;
}

int main()
{
	const char* msg = "test";
	const std::vector<unsigned char> binary(msg, msg + strlen(msg));
	const std::string encoded = Base64Encode(binary);
	std::cout << "encoded = " << encoded << std::endl;
	const std::vector<unsigned char> decoded = Base64Decode(encoded.c_str());
	std::cout << "decoded = ";
	for (unsigned char c : decoded) std::cout << c;
	std::cout << std::endl;
	return 0;
}

#endif

