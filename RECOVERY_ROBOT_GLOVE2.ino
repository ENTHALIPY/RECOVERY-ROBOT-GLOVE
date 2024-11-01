/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL61hxUIMwX"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "nFl5O8hvQsrvgwe57kPMRO4RnkMAS5i7"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiManager.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Adafruit_MLX90614.h>

String Heart_SpO2;

unsigned long lastUpdate=0;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AmericanStudy T1";
char pass[] = "66668888";

BlynkTimer timer;
WiFiManager wifiManager;


PulseOximeter pox;
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

float nhiptim, oxy, nhietdo;



// This function is called every time the device is connected to the Blynk.Cloud




void setup() {
  // Debug console
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  wifiManager.autoConnect("Ban tay tro luc2", "88888888");
  Serial.println();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
   if (!pox.begin()) {
    Serial.println("POX: FAILED");
    failed();
    for (;;)
      failed();
  } else {
    Serial.println("POX: SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_14_2MA);

  mlx.begin(0x5A);

  Wire.setClock(100000);


  
}

void loop() {
  Blynk.run();
  timer.run();
    pox.update();
    pox_mlx_read();
     Heart_SpO2 = "NHIPTIM:" +String(nhiptim)+"  SpO2:" +String(oxy) +"  THANNHIET:" +String(nhietdo) ;
 if (millis()- lastUpdate>3000){
 Blynk.virtualWrite(V7, Heart_SpO2);
 }
 
 
}

void pox_mlx_read() {
  nhiptim = pox.getHeartRate();
  oxy = pox.getSpO2();
  nhietdo = mlx.readObjectTempC();
}



void failed() {
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  delay(100);
  
}
