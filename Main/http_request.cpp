#include <ESP8266HTTPClient.h>
#include "status_manager.h"

#define SERVER_IP "http://192.168.1.71:8000/"


void http_post(const String data){
    
    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // Configurando la url para la peticion http
    http.begin(client, SERVER_IP "gps/data/" );  // HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    // Iniciamos la conexion y envio de la peticion HTTP header y body
    int httpCode = http.POST(data);


    if (httpCode > 0) {
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // Si hay respuesta positiva
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
        const int actValue = payload.toInt();
        actuador(actValue);
        green();
      }
    } else {
      // Si hay respuesta negativa
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      red();
    }
    http.end();
}
