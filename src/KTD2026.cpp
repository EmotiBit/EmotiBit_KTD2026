#include "KTD2026.h"

bool KTD2026::begin() {
    //_i2c->begin(); // interface is initialized before being passed to this class
    _i2c->beginTransmission(_address);
    if (_i2c->endTransmission())
        return false;

    return true;
    // ToDo: setup current level
    // ToDO: maybe setup PWM
}


uint8_t KTD2026::writeRegister(uint8_t reg, uint8_t value) {
    //Serial.print("writing to register: "); Serial.print(reg,HEX); Serial.print("\tvalue: "); Serial.println(value,HEX);
    _i2c->beginTransmission(_address);
    _i2c->write(reg);       // Register address
    _i2c->write(value);     // Value to set
    return (_i2c->endTransmission());
}

uint8_t KTD2026::setEnable()
{
    //writeRegister(KTD2026_REG_ENABLE, enable ? 0x01 : 0x00);
    return(writeRegister(KTD2026_REG_ENABLE, 0x00));
}

uint8_t KTD2026::setChannelCurrent(Channel channel, uint8_t value)
{
    uint8_t registerBankIdx, regAddr;
    switch(channel)
    {
        case Channel::CH1:
            registerBankIdx = (uint8_t)RegisterIndex::LED1_IOUT;
            regAddr = KTD2026_REG_CHANNEL1_IOUT;
            break;
        case Channel::CH2:
            registerBankIdx = (uint8_t)RegisterIndex::LED2_IOUT;
            regAddr = KTD2026_REG_CHANNEL2_IOUT;
            break;
        case Channel::CH3:
            registerBankIdx = (uint8_t)RegisterIndex::LED3_IOUT;
            regAddr = KTD2026_REG_CHANNEL3_IOUT;
            break;                
    }

    _registerBank[registerBankIdx] = value;
    return (writeRegister(regAddr, _registerBank[registerBankIdx]));
}

uint8_t KTD2026::getChannelControl()
{
    return _registerBank[(uint8_t)RegisterIndex::CHANNEL_CONTROL];
}

bool KTD2026::updateChannelMode(Channel channel, LedMode mode)
{
    uint8_t shiftCount = 0; // valid bits for channel 1 are 0b000000YY
    if(channel == Channel::CH2)
    {
        shiftCount = 2; // valid bits for channel 1 are 0b0000YY00
    }
    else if (channel == Channel::CH3)
    {
        shiftCount = 4;  // valid bits for channel 1 are 0b00YY0000
    }
    uint8_t mask;
    uint8_t& reg = _registerBank[(uint8_t)RegisterIndex::CHANNEL_CONTROL];
    if (mode == LedMode::ALWAYS_OFF)
    {
        mask = KTD2026_CH_SET_OFF_MASK << shiftCount;
        reg = reg & ~mask;
    }
    else if (mode == LedMode::ALWAYS_ON)
    {
        mask = KTD2026_CH_SET_ON_MASK << shiftCount;
        reg = reg & ~(mask<<1); // makes high bit 0
        reg = reg | mask; // makes low bit 1
    }
    else
    {
        // PWM not yet supported
        return false;
    }
    return true;
}

uint8_t KTD2026::sendChannelControl()
{
    return(writeRegister(KTD2026_REG_CHANNEL_CONTROL, _registerBank[(uint8_t)RegisterIndex::CHANNEL_CONTROL]));
}

uint8_t KTD2026::readRegister(uint8_t reg)
{
    // Need to write custom i2c wire functions to recreate the protocol spc'd in the datasheet
}