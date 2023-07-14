#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <TinyGPS++.h>
#include "status_manager.h"
#include "auth.h"
#include "http_request.h"

#define rxPin D8
#define txPin D7

TinyGPSPlus gps;
SoftwareSerial SerialGps(rxPin, txPin);


#define WIFI_SSID "INFINITUM594F"    // nombre de la red wifi
#define WIFI_PASSWORD "sU5I4AIn3C"   // contraseña de la red wifi

const String UUID =  "58911";

void setup() {
  // SE ESTABLECE LA VELOCIDAD
  Serial.begin(115200); 
  SerialGps.begin(9600);

  // INICIAMOS LA CONEXION AL WIFI.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
  }
  Serial.println();
  Serial.print("conectado !! ");
  Serial.println(WiFi.localIP());

  // CONFIGURAMOS PINES DE SALIDA DIGITAL----------------
  setup_pines();
}

void loop() {

  while (SerialGps.available() > 0)
    if (gps.encode(SerialGps.read())){
      white();
      displayInfo();

      if (WiFi.status() == WL_CONNECTED ){
        yellow();
        const String latitude = String(gps.location.lat(), 6);
        const String longitude = String(gps.location.lng(), 6);
        const String date = String( gps.date.day()) + "/" + String(gps.date.month()) + "/" + String(gps.date.year());
        const String hour = "0" + String(gps.time.hour() - 6) + ":" + String(gps.time.minute()) + ":" + String(gps.time.second());
        const String coord = F("{\"latitud\":\"") + latitude + F("\", \"longitud\":\"") + longitude + F("\", \"fecha\":\"") + date + F("\", \"hora\":\"") + hour + F("\"}");
        // boolean auth = http_auth(UUID);
        // if (auth){
          http_post(coord);
        // }
      }else{
        white();
      }
      
    }

    if (millis() > 5000 && gps.charsProcessed() < 10){
      Serial.println(F("No GPS detected: check wiring."));
      red();
      while(true);
    }

}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}