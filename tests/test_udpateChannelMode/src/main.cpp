#include <Arduino.h>
#include "KTD2026.h"

KTD2026 ledDriver(KTD2026_I2C_ADDRESS);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  Serial.print("Channel control register: 0x"); Serial.println(ledDriver.getChannelControl(),HEX);
  
  ledDriver.updateChannelMode(KTD2026::Channel::CH1, KTD2026::LedMode::ALWAYS_ON);
  Serial.println("Channel 1 set");
  Serial.print("Channel control register: 0x"); Serial.println(ledDriver.getChannelControl(),HEX);
  
  ledDriver.updateChannelMode(KTD2026::Channel::CH2, KTD2026::LedMode::ALWAYS_ON);
  Serial.println("Channel 2 set");
  Serial.print("Channel control register: 0x"); Serial.println(ledDriver.getChannelControl(),HEX);
  
  ledDriver.updateChannelMode(KTD2026::Channel::CH3, KTD2026::LedMode::ALWAYS_ON);
  Serial.println("Channel 3 set");
  Serial.print("Channel control register: 0x"); Serial.println(ledDriver.getChannelControl(),HEX);
  
  ledDriver.updateChannelMode(KTD2026::Channel::CH3, KTD2026::LedMode::ALWAYS_OFF);
  Serial.println("Channel 3 reset");
  Serial.print("Channel control register: 0x"); Serial.println(ledDriver.getChannelControl(),HEX);
  
  ledDriver.updateChannelMode(KTD2026::Channel::CH2, KTD2026::LedMode::ALWAYS_OFF);
  Serial.println("Channel 2 reset");
  Serial.print("Channel control register: 0x"); Serial.println(ledDriver.getChannelControl(),HEX);
  
  ledDriver.updateChannelMode(KTD2026::Channel::CH1, KTD2026::LedMode::ALWAYS_OFF);
  Serial.println("Channel 1 reset");
  Serial.print("Channel control register: 0x"); Serial.println(ledDriver.getChannelControl(),HEX);
  
  Serial.print("end of test");
  while(1);
}

void loop() {
 
}