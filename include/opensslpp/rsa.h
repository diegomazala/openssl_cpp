﻿#pragma once

#include "aes_cbc.h"
#include "random.h"

namespace opensslpp
{
    template <size_t Bits, class Aes, class Hash>
    class Rsa final
    {
        using RsaT = Rsa<Bits, Aes, Hash>;
    public:
        static constexpr size_t KeySize = Bits / 8;
        using EncryptedKey = std::array<uint8_t, KeySize>;

        using Iv = typename Aes::Iv;

        static std::unique_ptr<RsaT> createNewKeys()
        {
            KeyContextPtr context(EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr), EVP_PKEY_CTX_free);
            if (!context)
                return nullptr;

            if (EVP_PKEY_keygen_init(context.get()) != Success)
                return nullptr;

            if (EVP_PKEY_CTX_set_rsa_keygen_bits(context.get(), Bits) != Success)
                return nullptr;

            EVP_PKEY* key = nullptr;

            if (EVP_PKEY_keygen(context.get(), &key) != Success)
                return nullptr;

            return std::unique_ptr<RsaT>(new RsaT(KeyPtr(key, EVP_PKEY_free)));
        }

        static std::unique_ptr<RsaT> createWithPublicKey(const std::string& publicKey)
        {
            auto bio = makeBio(BIO_new_mem_buf(publicKey.c_str(), static_cast<int>(publicKey.size())));
            KeyPtr key(PEM_read_bio_PUBKEY(bio.get(), nullptr, nullptr, nullptr), EVP_PKEY_free);
            if (!key)
                return nullptr;
            return std::unique_ptr<RsaT>(new RsaT(std::move(key)));
        }

        static std::unique_ptr<RsaT> createWithPrivateKey(const std::string& privateKey, std::string passPhrase = std::string())
        {
            auto bio = makeBio(BIO_new_mem_buf(privateKey.c_str(), static_cast<int>(privateKey.size())));
            auto ptr = const_cast<char*>(passPhrase.c_str());
            KeyPtr key(PEM_read_bio_PrivateKey(bio.get(), nullptr, nullptr, ptr), EVP_PKEY_free);
            if (!key)
                return nullptr;
            return std::unique_ptr<RsaT>(new RsaT(std::move(key)));
        }

        std::string publicKey() const
        {
            return keyToString([this](BIO* bio)
            {
                return PEM_write_bio_PUBKEY(bio, rsaKey_.get());
            });
        }

        std::string privateKey() const
        {
            return keyToString([this](BIO* bio)
            {
                return PEM_write_bio_PrivateKey(bio, rsaKey_.get(), nullptr, nullptr, 0, nullptr, nullptr);
            });
        }

        std::string privateKeyPKCS8(std::string passPhrase) const
        {
            return keyToString([this, &passPhrase](BIO* bio)
            {
                auto ptr = const_cast<char*>(passPhrase.c_str());
                return PEM_write_bio_PKCS8PrivateKey(bio, rsaKey_.get(), Aes::Mode(), nullptr, 0, nullptr, ptr);
            });
        }

        bool encrypt(const std::string& plainText, EncryptedKey& key, Iv& iv, std::vector<uint8_t>& cipher) const
        {
            return encrypt(reinterpret_cast<const uint8_t*>(plainText.c_str()), plainText.size(), key, iv, cipher);
        }

        bool encrypt(const uint8_t* plainData, size_t plainDataSize, EncryptedKey& key, Iv& iv, std::vector<uint8_t>& cipher) const
        {
            CipherContextPtr context(EVP_CIPHER_CTX_new(), EVP_CIPHER_CTX_free);
            if (!context)
                return false;

            const int publicKeysCount = 1;
            uint8_t* keys[] = { key.data() };
            EVP_PKEY* publicKeys[] = { rsaKey_.get() };

            int keySize = 0;
            if (EVP_SealInit(context.get(), Aes::Mode(), keys, &keySize, iv.data(), publicKeys, publicKeysCount) != publicKeysCount)
                return false;

            const size_t cipherSize = Aes::getCipherSize(plainDataSize);
            cipher.resize(cipherSize);

            int size = 0;
            if (EVP_SealUpdate(context.get(), cipher.data(), &size, plainData, static_cast<int>(plainDataSize)) != Success)
                return false;

            if (EVP_SealFinal(context.get(), cipher.data() + size, &size) != Success)
                return false;

            return true;
        }

        bool decrypt(const EncryptedKey& key, const Iv& iv, const std::vector<uint8_t>& cipher, std::vector<uint8_t>& plainData) const
        {
            CipherContextPtr context(EVP_CIPHER_CTX_new(), EVP_CIPHER_CTX_free);
            if (!context)
                return false;

            if (EVP_OpenInit(context.get(), Aes::Mode(), key.data(), static_cast<int>(key.size()), iv.data(), rsaKey_.get()) != Success)
                return false;

            plainData.resize(cipher.size());

            int size = 0;
            if (EVP_OpenUpdate(context.get(), plainData.data(), &size, cipher.data(), static_cast<int>(cipher.size())) != Success)
                return false;

            auto plainDataSize = size;

            if (EVP_OpenFinal(context.get(), plainData.data() + size, &size) != Success)
                return false;

            plainDataSize += size;

            plainData.resize(plainDataSize);

            return true;
        }

        bool sign(const std::string& plainText, std::vector<uint8_t>& signature)
        {
            DigestContextPtr context(EVP_MD_CTX_create(), EVP_MD_CTX_free);
            if (!context)
                return false;

            if (EVP_DigestSignInit(context.get(), nullptr, Hash::Function(), nullptr, rsaKey_.get()) != Success)
                return false;

            if (EVP_DigestSignUpdate(context.get(), plainText.c_str(), plainText.size()) != Success)
                return false;

            size_t size = 0;
            if (EVP_DigestSignFinal(context.get(), nullptr, &size) != Success)
                return false;

            signature.resize(size);

            if (EVP_DigestSignFinal(context.get(), signature.data(), &size) != Success)
                return false;

            return true;
        }

        bool isCorrectSignature(const std::string& plainText, const std::vector<uint8_t>& signature)
        {
			DigestContextPtr context(EVP_MD_CTX_new(), EVP_MD_CTX_free); // OpenSSL >= 1.1
			//DigestContextPtr context(EVP_MD_CTX_create(), EVP_MD_CTX_destroy); // OpenSSL <= 1.0

            if (!context)
                return false;

            if (EVP_DigestVerifyInit(context.get(), nullptr, Hash::Function(), nullptr, rsaKey_.get()) != Success)
                return false;

            if (EVP_DigestVerifyUpdate(context.get(), plainText.c_str(), plainText.size()) != Success)
                return false;

            if (EVP_DigestVerifyFinal(context.get(), signature.data(), signature.size()) != Success)
                return false;

            return true;
        }

        Rsa(const Rsa&) = delete;
        Rsa& operator=(const Rsa&) = delete;

        Rsa(Rsa&&) = delete;
        Rsa& operator=(Rsa&&) = delete;

        ~Rsa()
        {
        }

    private:
        Rsa(KeyPtr&& key)
            : rsaKey_(std::move(key))
        {
        }

    private:
        KeyPtr rsaKey_;
    };

    using Rsa2048 = Rsa<2048, Aes256Cbc, Sha256Type>;
}
