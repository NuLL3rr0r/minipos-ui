#ifndef ERTEBAT_CRYPTO_HPP
#define ERTEBAT_CRYPTO_HPP


#include <memory>
#include <string>
#include <cstddef>

namespace Ertebat {
    class Crypto;
}

class Ertebat::Crypto
{
public:
    typedef unsigned char Byte_t;

private:
    struct Impl;
    std::unique_ptr<Impl> m_pimpl;

public:
    static bool Encrypt(const std::string &plainText, std::string &out_encodedText,
                        const Byte_t *key, std::size_t keyLen, const Byte_t *iv, std::size_t ivLen);
    static bool Encrypt(const std::string &plainText, std::string &out_encodedText,
                        std::string &out_error,
                        const Byte_t *key, std::size_t keyLen, const Byte_t *iv, std::size_t ivLen);
    static bool Decrypt(const std::string &cipherText, std::string &out_recoveredText,
                        const Byte_t *key, std::size_t keyLen, const Byte_t *iv, std::size_t ivLen);
    static bool Decrypt(const std::string &cipherText, std::string &out_recoveredText,
                        std::string &out_error,
                        const Byte_t *key, std::size_t keyLen, const Byte_t *iv, std::size_t ivLen);
    static bool GenerateHash(const char *text, std::string &out_digest);
    static bool GenerateHash(const std::string &text, std::string &out_digest);
    static bool GenerateHash(const char *text, std::string &out_digest,
                             std::string &out_error);
    static bool GenerateHash(const std::string &text, std::string &out_digest,
                             std::string &out_error);
    static int Base64Decode(char value);
    static int Base64Decode(const char *code, const int length, char *out_plainText);
    static void Base64Decode(std::istream &inputStream, std::ostream &outputStream);
    static int Base64Encode(char value);
    static int Base64Encode(const char *code, const int length, char *out_plainText);
    static int Base64EncodeBlockEnd(char *out_plainText);
    static void Base64Encode(std::istream &inputStream, std::ostream &outputStream);

public:
    Crypto(const Byte_t *key, std::size_t keyLen, const Byte_t *iv, std::size_t ivLen);
    ~Crypto();

public:
    bool Encrypt(const std::string &plainText, std::string &out_encodedText);
    bool Encrypt(const std::string &plainText, std::string &out_encodedText,
                 std::string &out_error);
    bool Decrypt(const std::string &cipherText, std::string &out_recoveredText);
    bool Decrypt(const std::string &cipherText, std::string &out_recoveredText,
                 std::string &out_error);
};


#endif /* ERTEBAT_CRYPTO_HPP */

