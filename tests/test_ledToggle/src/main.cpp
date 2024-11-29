#include <Arduino.h>
#include "KTD2026.h"

KTD2026 ledDriver(KTD2026_I2C_ADDRESS);

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
  ledDriver.setEnable();
}

void loop() {
  for(int i=0; i<(int)KTD2026::Channel::length; i++)
  {
    ledDriver.updateChannelMode((KTD2026::Channel)i, KTD2026::LedMode::ALWAYS_ON);
    ledDriver.sendChannelControl();
    delay(500);
  }
  for(int i=0; i<(int)KTD2026::Channel::length; i++)
  {
    ledDriver.updateChannelMode((KTD2026::Channel)i, KTD2026::LedMode::ALWAYS_OFF);
    ledDriver.sendChannelControl();
    delay(500);
  }
}