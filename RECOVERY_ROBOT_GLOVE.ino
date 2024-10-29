/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL623qkyuwg"
#define BLYNK_TEMPLATE_NAME "RECOVERY ROBOT GLOVE"
#define BLYNK_AUTH_TOKEN "85XcWS4fh1LQ1tx_L3-jYMLnlr8Ef94R"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiManager.h>
#include <Wire.h>




// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AmericanStudy T1";
char pass[] = "66668888";

int lastBtn1State = HIGH;
int btn1State, btn2State, btn3State, btn4State, btn5State, btn6State;
int lastBtn2State = HIGH, lastBtn3State = HIGH, lastBtn4State = HIGH, lastBtn5State = HIGH, lastBtn6State = HIGH;
unsigned long btn1PressTime = 0, btn2PressTime = 0, btn3PressTime = 0, btn4PressTime = 0, btn5PressTime = 0, btn6PressTime = 0;
const unsigned long longPressDuration = 100;
int nut1 = 0, nut2 = 0, nut3 = 0, nut4 = 0, nut5 = 0, nut6 = 0;
int value1, value2, value3, value4, value5, value6;
BlynkTimer timer;
WiFiManager wifiManager;



// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0) {
  // Set incoming value from pin V0 to a variable
  value1 = param.asInt();
}
BLYNK_WRITE(V1) {
  // Set incoming value from pin V0 to a variable
  value2 = param.asInt();
}
BLYNK_WRITE(V3) {
  // Set incoming value from pin V0 to a variable
  value3 = param.asInt();
}
BLYNK_WRITE(V4) {
  // Set incoming value from pin V0 to a variable
  value4 = param.asInt();
}
BLYNK_WRITE(V5) {
  // Set incoming value from pin V0 to a variable
  value5 = param.asInt();
}
BLYNK_WRITE(V6) {
  // Set incoming value from pin V0 to a variable
  value6 = param.asInt();
}


// This function is called every time the device is connected to the Blynk.Cloud


// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent() {
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup() {
  // Debug console
  Serial.begin(115200);
  wifiManager.autoConnect("RECOVERY ROBOT GLOVE", "88888888");

  Serial.println();
  //Wire.setClock(400000);
  Blynk.begin(BLYNK_AUTH_TOKEN, WiFi.SSID().c_str(), WiFi.psk().c_str());
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D7, HIGH);
  digitalWrite(D4, HIGH);
  digitalWrite(D5, HIGH);
  digitalWrite(D6, HIGH);

  // Register a callback for the beat detection
  timer.setInterval(1000L, myTimerEvent);
}

void loop() {
  Blynk.run();
  timer.run();

  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!

  btn1State = value1;  // nhan tren 3s ==> doi mode // nhan duoi 3s doi che do xem man hinh
  btn2State = value2;
  btn3State = value3;
  btn4State = value4;
  btn5State = value5;
  btn6State = value6;

  if (btn1State != lastBtn1State) {
    if (btn1State == HIGH) {
      btn1PressTime = millis();
    } else {
      if (millis() - btn1PressTime > longPressDuration) {
        // Serial.println("111111111111");
        nut1 = 1;
      }
    }
  }
  if (btn2State != lastBtn2State) {
    if (btn2State == HIGH) {
      btn2PressTime = millis();
    } else {
      if (millis() - btn2PressTime > longPressDuration) {
        // Serial.println("222222222222");
        nut2 = 1;
      }
    }
  }
  if (btn3State != lastBtn3State) {
    if (btn3State == HIGH) {
      btn3PressTime = millis();
    } else {
      if (millis() - btn3PressTime > longPressDuration) {
        // Serial.println("333333333333");
        nut3 = 1;
      }
    }
  }
  if (btn4State != lastBtn4State) {
    if (btn4State == HIGH) {
      btn4PressTime = millis();
    } else {
      if (millis() - btn4PressTime > longPressDuration) {
        // Serial.println("444444444444");
        nut4 = 1;
      }
    }
  }
  if (btn5State != lastBtn5State) {
    if (btn5State == HIGH) {
      btn5PressTime = millis();
    } else {
      if (millis() - btn5PressTime > longPressDuration) {
        ///Serial.println("555555555555");
        nut5 = 1;
      }
    }
  }
  if (btn6State != lastBtn6State) {
    if (btn6State == HIGH) {
      btn6PressTime = millis();
    } else {
      if (millis() - btn6PressTime > longPressDuration) {
        // Serial.println("666666666666");
        nut6 = 1;
      }
    }
  }
  Control();

  // Serial.print(nut1);
  // Serial.print("\t");
  // Serial.print(nut2);
  // Serial.print("\t");
  // Serial.print(nut3);
  // Serial.print("\t");
  // Serial.print(nut4);
  // Serial.print("\t");
  // Serial.print(nut5);
  // Serial.print("\t");
  // Serial.println(nut6);
  lastBtn1State = btn1State;
  lastBtn2State = btn2State;
  lastBtn3State = btn3State;
  lastBtn4State = btn4State;
  lastBtn5State = btn5State;
  lastBtn6State = btn6State;
  nut1 = 0;
  nut2 = 0;
  nut3 = 0;
  nut4 = 0;
  nut5 = 0;
  nut6 = 0;
}

void Control() {

  if (nut1 == 1) {
    digitalWrite(D1, LOW);
    delay(100);
    digitalWrite(D1, HIGH);
  } else if (nut2 == 1) {
    digitalWrite(D2, LOW);
    delay(100);
    digitalWrite(D2, HIGH);
  } else if (nut3 == 1) {
    digitalWrite(D7, LOW);
    delay(100);
    digitalWrite(D7, HIGH);
  } else if (nut4 == 1) {
    digitalWrite(D4, LOW);
    delay(100);
    digitalWrite(D4, HIGH);
  } else if (nut5 == 1) {
    digitalWrite(D5, LOW);
    delay(100);
    digitalWrite(D5, HIGH);
  } else if (nut6 == 1) {
    digitalWrite(D6, LOW);
    delay(100);
    digitalWrite(D6, HIGH);
  } else {
  }
}
