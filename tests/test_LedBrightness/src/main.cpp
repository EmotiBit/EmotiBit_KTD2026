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
  
  ledDriver.updateChannelMode(KTD2026::Channel::CH1, KTD2026::LedMode::ALWAYS_ON);
  ledDriver.sendChannelControl();
  Serial.println("notice LED brightness at 10mA");
  delay(3000);
  Serial.println("reducing brightness to 2mA");
  //ledDriver.setChannelCurrent(channel, 0x20); // 4mA/24mA*192steps = 32steps = 0x20steps
  ledDriver.setChannelCurrent(KTD2026::Channel::CH1, 0x10); 
  delay(3000);
  ledDriver.updateChannelMode(KTD2026::Channel::CH1, KTD2026::LedMode::ALWAYS_OFF);
  ledDriver.sendChannelControl();

  ledDriver.updateChannelMode(KTD2026::Channel::CH2, KTD2026::LedMode::ALWAYS_ON);
  ledDriver.sendChannelControl();
  Serial.println("notice LED brightness at 10mA");
  delay(3000);
  Serial.println("reducing brightness to 2mA");
  //ledDriver.setChannelCurrent(channel, 0x20); // 4mA/24mA*192steps = 32steps = 0x20steps
  ledDriver.setChannelCurrent(KTD2026::Channel::CH2, 0x10); 
  delay(3000);
  ledDriver.updateChannelMode(KTD2026::Channel::CH2, KTD2026::LedMode::ALWAYS_OFF);
  ledDriver.sendChannelControl();

  ledDriver.updateChannelMode(KTD2026::Channel::CH3, KTD2026::LedMode::ALWAYS_ON);
  ledDriver.sendChannelControl();
  Serial.println("notice LED brightness at 10mA");
  delay(3000);
  Serial.println("reducing brightness to 2mA");
  //ledDriver.setChannelCurrent(channel, 0x20); // 4mA/24mA*192steps = 32steps = 0x20steps
  ledDriver.setChannelCurrent(KTD2026::Channel::CH3, 0x10); 
  delay(3000);
  ledDriver.updateChannelMode(KTD2026::Channel::CH3, KTD2026::LedMode::ALWAYS_OFF);
  ledDriver.sendChannelControl();
}

void loop() {
  // Test setting different brightness for all channels
 
}