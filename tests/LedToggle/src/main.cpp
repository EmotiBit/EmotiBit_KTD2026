#include <Arduino.h>
#include "KTD2026.h"

KTD2026 ledDriver;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Wire.begin();
  Wire.setClock(400000);
  if (ledDriver.begin())
  {
    Serial.println("sesnor initialization complete");
  }
  else
  {
    Serial.println("Sensor initialization failed.");
    while(1);
  }
  ledDriver.setEnabled();
}

void loop() {
  // put your main code here, to run repeatedly:
  ledDriver.setChannel1();
  delay(1000);
  ledDriver.setChannel2();
  delay(1000);
  ledDriver.setChannel3();
  delay(1000);
  ledDriver.resetChannel1();
  delay(1000);
  ledDriver.resetChannel2();
  delay(1000);
  ledDriver.resetChannel3();
  delay(1000);
}

