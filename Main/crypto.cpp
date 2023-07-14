#include <Crypto.h>
#include <RSA.h>

RSAKey privateKey;
RSAKey publicKey;

void keygenerator() {
  // Generar un nuevo par de claves
  RSA_gen_key(512, publicKey, privateKey);

  // Imprimir las claves generadas
  Serial.println("Clave pública:");
  publicKey.dump(Serial);
  Serial.println();

  Serial.println("Clave privada:");
  privateKey.dump(Serial);
  Serial.println();
}

void cipherKPI(){
  
}