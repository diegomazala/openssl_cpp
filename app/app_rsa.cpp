#include <opensslpp/rsa.h>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
#include <iostream>

void test_common()
{

    auto newRsa = opensslpp::Rsa2048::createNewKeys();
    assert(newRsa != nullptr);

    const auto publicKey = newRsa->publicKey();
    const auto privateKey = newRsa->privateKey();

    auto publicRsa = opensslpp::Rsa2048::createWithPublicKey(publicKey);
    assert(publicRsa != nullptr);
    assert(publicRsa->publicKey() == publicKey);

    auto privateRsa = opensslpp::Rsa2048::createWithPrivateKey(privateKey);
    assert(privateRsa != nullptr);
    assert(privateRsa->privateKey() == privateKey);

    const std::string plainText = "1234567890abcdef-+=!qwerty0987654321ABCDEF";

    opensslpp::Rsa2048::EncryptedKey encryptedKey;
    opensslpp::Rsa2048::Iv iv;

    std::vector<uint8_t> cipher;

    assert(publicRsa->encrypt(plainText, encryptedKey, iv, cipher));

    std::vector<uint8_t> plainData;

    assert(privateRsa->decrypt(encryptedKey, iv, cipher, plainData));

    assert(plainText == std::string(reinterpret_cast<char*>(plainData.data()), plainData.size()));

    std::vector<uint8_t> signature;
    assert(privateRsa->sign(plainText, signature));

    assert(publicRsa->isCorrectSignature(plainText, signature));
}

void test_passPhrase()
{
    auto newRsa = opensslpp::Rsa2048::createNewKeys();
    assert(newRsa != nullptr);

    const std::string passPhrase = "testPhrase";

    const auto publicKey = newRsa->publicKey();
    const auto privateKey = newRsa->privateKey();
    const auto cryptedPrivateKey = newRsa->privateKeyPKCS8(passPhrase);

    assert(privateKey != cryptedPrivateKey);

    auto publicRsa = opensslpp::Rsa2048::createWithPublicKey(publicKey);
    assert(publicRsa != nullptr);
    assert(publicRsa->publicKey() == publicKey);

    auto privateRsa = opensslpp::Rsa2048::createWithPrivateKey(cryptedPrivateKey, passPhrase);
    assert(privateRsa != nullptr);
    assert(privateRsa->privateKey() == privateKey);

    auto invalid = opensslpp::Rsa2048::createWithPrivateKey(cryptedPrivateKey);
    assert(invalid == nullptr);
    const std::string plainText = "1234567890abcdef-+=!qwerty0987654321ABCDEF";

    opensslpp::Rsa2048::EncryptedKey encryptedKey;
    opensslpp::Rsa2048::Iv iv;

    std::vector<uint8_t> cipher;

    assert(publicRsa->encrypt(plainText, encryptedKey, iv, cipher));

    std::vector<uint8_t> plainData;

    assert(privateRsa->decrypt(encryptedKey, iv, cipher, plainData));

    assert(plainText == std::string(reinterpret_cast<char*>(plainData.data()), plainData.size()));

    std::vector<uint8_t> signature;
    assert(privateRsa->sign(plainText, signature));

    assert(publicRsa->isCorrectSignature(plainText, signature));
}

int main()
{
    test_common();
    test_passPhrase();
    return EXIT_SUCCESS;
}