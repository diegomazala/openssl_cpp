
#include <opensslpp/aes_gcm.h>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>

int main()
{
#if 0
    auto newAes = opensslpp::Aes256Gcm::createNewKey();
    assert(newAes != nullptr);

    const auto base64Key = newAes->base64Key();
    auto aes = opensslpp::Aes256Gcm::createWithKey(base64Key);
	assert(aes != nullptr);
	assert(aes->base64Key() == base64Key);

    const std::string plainText = "1234567890abcdef-+=!qwerty0987654321ABCDEF";

    std::vector<uint8_t> cipher;
    opensslpp::Aes256Gcm::Iv iv;
    opensslpp::Aes256Gcm::Tag tag;

    assert(aes->encrypt(plainText, cipher, iv, tag));

    std::vector<uint8_t> plainData;

    assert(aes->decrypt(cipher, iv, tag, plainData));

    assert(plainText == std::string(reinterpret_cast<char*>(plainData.data()), plainData.size()));


	std::cout << "key      : " << base64Key << std::endl;
	std::cout << "encrypted: " << plainText << std::endl;

	std::cout << "decrypted: ";
	for (auto v : plainData)
		std::cout << v;
	std::cout << std::endl;
#endif

    return EXIT_SUCCESS;
}
