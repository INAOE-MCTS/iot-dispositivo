#include <Crypto.h>
#include <AES.h>
#include <CBC.h>
#include <ArduinoCryptolib.h>

// Define tus claves públicas y privadas aquí (en formato uint8_t[])
const uint8_t publicKey[] = { ... };
const size_t publicKeySize = sizeof(publicKey);

const uint8_t privateKey[] = { ... };
const size_t privateKeySize = sizeof(privateKey);


void encryptRSA(const uint8_t* publicKey, size_t publicKeySize, const uint8_t* dataToEncrypt, size_t dataSize, uint8_t* encryptedData, size_t encryptedDataSize) {
  RSAWrapper rsa;
  rsa.setPublicKey(publicKey, publicKeySize);
  rsa.encrypt(dataToEncrypt, dataSize, encryptedData, encryptedDataSize);
}

void decryptRSA(const uint8_t* privateKey, size_t privateKeySize, const uint8_t* encryptedData, size_t encryptedDataSize, uint8_t* decryptedData, size_t decryptedDataSize) {
  RSAWrapper rsa;
  rsa.setPrivateKey(privateKey, privateKeySize);
  rsa.decrypt(encryptedData, encryptedDataSize, decryptedData, decryptedDataSize);
}



void encryptAES_CBC(const uint8_t* key, const uint8_t* iv, const uint8_t* dataToEncrypt, size_t dataSize, uint8_t* encryptedData) {
  AES aes;
  CBC<AES> cbc;

  aes.setKey(key, AES::DEFAULT_KEYLENGTH);
  cbc.setKey(aes, AES::DEFAULT_KEYLENGTH, iv);

  size_t paddingSize = AES::BLOCKSIZE - (dataSize % AES::BLOCKSIZE);
  uint8_t paddedData[dataSize + paddingSize];
  memcpy(paddedData, dataToEncrypt, dataSize);
  memset(paddedData + dataSize, paddingSize, paddingSize);

  cbc.encrypt(paddedData, encryptedData, dataSize + paddingSize);
}

void decryptAES_CBC(const uint8_t* key, const uint8_t* iv, const uint8_t* encryptedData, size_t dataSize, uint8_t* decryptedData) {
  AES aes;
  CBC<AES> cbc;

  aes.setKey(key, AES::DEFAULT_KEYLENGTH);
  cbc.setKey(aes, AES::DEFAULT_KEYLENGTH, iv);

  cbc.decrypt(encryptedData, decryptedData, dataSize);
}
