#include <SoftwareSerial.h>
#include <ESP8266HTTPClient.h>
#include "status_manager.h"

#define SERVER_IP "http://192.168.1.71:8000/"
// String UUID = "7E48A7A8-AB3C-484C-8EBA-027FB8F84F44"

boolean http_auth(String UUID){
    
    WiFiClient client;
    HTTPClient http;

    boolean response = false;

    Serial.print("[HTTP] begin...\n");
    // Configurando la url para la peticion http
    http.begin(client, SERVER_IP "api/v1/gps/" );  // HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    // Iniciamos la conexion y envio de la peticion HTTP header y body
    const String data = F("{\"UUID\":\"") + UUID + F("\"}");
    int httpCode = http.POST(data);


    if (httpCode > 0) {
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // Si hay respuesta positiva
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
        authenticated();
        response = true;
      }
    } else {
      // Si hay respuesta negativa
      Serial.printf("[HTTP] POST... Unauthenticated, error: %s\n", http.errorToString(httpCode).c_str());
      not_authenticated();
      response = false;
    }
    http.end();

    return response;
}