#pragma once
#include <Wire.h>
#include "Arduino.h"


// Define the I²C address for the KTD2026
#define KTD2026_I2C_ADDRESS 0x30  // Update according to the datasheet

// Register Addresses (from the KTD2026 datasheet)
#define KTD2026_REG_ENABLE 0x00
#define KTD2026_REG_CHANNEL_CONTROL 0x04

#define KTD2026_MASK_CH_OFF 0x00
#define KTD2026_MASK_CH_ON 0x01
#define KTD2026_CHANNEL_CTRL_1_ON 0x01
#define KTD2026_CHANNEL_CTRL_2_ON 0x04
#define KTD2026_CHANNEL_CTRL_3_ON 0x10


// Driver class for KTD2026
class KTD2026 {
private:
    uint8_t _address;
    TwoWire* _i2c;
    uint32_t _speed;
    uint8_t _controlRegister = 0x00; 

public:
    // Constructor
    KTD2026(uint8_t i2cAddress = KTD2026_I2C_ADDRESS, TwoWire* i2c = &Wire, uint32_t speed = 400000)
        : _address(i2cAddress)
        , _i2c(i2c)
        , _speed(speed) {}

    // Initialize the I²C interface
    bool begin() {
        //_i2c->begin(); // interface is initialized before being passed to this class
        _i2c->beginTransmission(_address);
        if (_i2c->endTransmission())
            return false;

        return true;
        // ToDo: setup current level
        // ToDO: maybe setup PWM
    }

    // Enable or disable the KTD2026
    void setEnabled() {
        //writeRegister(KTD2026_REG_ENABLE, enable ? 0x01 : 0x00);
        writeRegister(KTD2026_REG_ENABLE, 0x00);

    }

    // Write to a KTD2026 register
    bool writeRegister(uint8_t reg, uint8_t value) {
        _i2c->beginTransmission(_address);
        _i2c->write(reg);       // Register address
        _i2c->write(value);     // Value to set
        return (_i2c->endTransmission());
    }

    uint8_t readRegister(uint8_t reg)
    {
        _i2c->beginTransmission(_address);
        _i2c->write(reg);       // Register address
        _i2c->endTransmission();
        _i2c->requestFrom(_address, 1); // request 1 byter of data
        return (_i2c->read());
    }

    bool setChannel1()
    {
        //uint8_t regVal = readRegister(KTD2026_REG_CHANNEL_CONTROL);
        //Serial.print("Current register value: "); Serial.println(regVal, HEX);
        _controlRegister = _controlRegister | 0b00000011; // mask
        _controlRegister = _controlRegister & 0b11111101;
        return(writeRegister(KTD2026_REG_CHANNEL_CONTROL, _controlRegister));
    }

    bool resetChannel1()
    {
        //uint8_t regVal = readRegister(KTD2026_REG_CHANNEL_CONTROL);
        //Serial.print("Current register value: "); Serial.println(regVal, HEX);
        _controlRegister = _controlRegister | 0b00000011; // mask
        _controlRegister = _controlRegister & 0b11111100;
        return(writeRegister(KTD2026_REG_CHANNEL_CONTROL, _controlRegister));
    }
    
    bool setChannel2()
    {
        _controlRegister = _controlRegister | 0b00001100; // mask
        _controlRegister = _controlRegister & 0b11110111;
        return(writeRegister(KTD2026_REG_CHANNEL_CONTROL, _controlRegister));
    }

    bool resetChannel2()
    {
        _controlRegister = _controlRegister | 0b00001100; // mask
        _controlRegister = _controlRegister & 0b11110011;
        return(writeRegister(KTD2026_REG_CHANNEL_CONTROL, _controlRegister));
    }
    bool setChannel3()
    {
        _controlRegister = _controlRegister | 0b00110000; // mask
        _controlRegister = _controlRegister & 0b11011111;
        return(writeRegister(KTD2026_REG_CHANNEL_CONTROL, _controlRegister));
    }

    bool resetChannel3()
    {
        _controlRegister = _controlRegister | 0b00110000; // mask
        _controlRegister = _controlRegister & 0b11001111;
        return(writeRegister(KTD2026_REG_CHANNEL_CONTROL, _controlRegister));
    }
};
