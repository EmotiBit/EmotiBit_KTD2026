#pragma once
#include <Wire.h>
#include "Arduino.h"


// Define the I²C address for the KTD2026
#define KTD2026_I2C_ADDRESS 0x30  //!< I2C address for KTD2026 
#define KTD2026B_I2C_ADDRESS 0x31  //!< I2C address for KTD2026B

// Register Addresses (from the KTD2026 datasheet)
#define KTD2026_REGISTER_BANK_SIZE 9  //<! KTD2026 register bank size
#define KTD2026_REG_ENABLE 0x00
#define KTD2026_REG_CHANNEL_CONTROL 0x04
#define KTD2026_REG_CHANNEL1_IOUT 0x06
#define KTD2026_REG_CHANNEL2_IOUT 0x07
#define KTD2026_REG_CHANNEL3_IOUT 0x08

#define KTD2026_CH_SET_OFF_MASK 0x03 // 0b00000011
#define KTD2026_CH_SET_ON_MASK 0x01  // 0b00000001

// Driver class for KTD2026
class KTD2026 {
private:
    uint8_t _address;
    TwoWire* _i2c;
    uint8_t _controlRegister = 0x00;
    uint8_t _registerBank[KTD2026_REGISTER_BANK_SIZE] = {0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x4F, 0x4F, 0x4F}; // POR values from the datasheet
    enum struct RegisterIndex : uint8_t{
        ENABLE_RST = 0,
        FLASH_PERIOD,
        FLASH_ON_TIME1,
        FLASH_ON_TIME2,
        CHANNEL_CONTROL,
        RAMP_RATE,
        LED1_IOUT,
        LED2_IOUT,
        LED3_IOUT,
        length
    };


public:
    enum struct Channel{
        CH1 = 0,
        CH2,
        CH3,
        length
    };

    enum struct LedMode{
        ALWAYS_OFF = 0,
        ALWAYS_ON,
        PWM1,
        PWM2,
        length
    };

    /*!
        @brief Constructor
        @param i2cAddress IC I2C address. Defaults to KTD2026
        @param i2c TwoWire instance of I2C. Defaults to Wire
    */
    KTD2026(uint8_t i2cAddress = KTD2026_I2C_ADDRESS, TwoWire* i2c = &Wire)
        : _address(i2cAddress)
        , _i2c(i2c) {}

    /*!
        @brief Pings IC to confirm presence. Fails, if IC not detected
        @return True if successful, else false
    */
    bool begin();

    /*!
        @brief Enable the controller
        @return I2C error code
    */
    uint8_t setEnable();

    /*!
        @brief Write a value to register
        @param reg Register to write
        @param value Value to write
        @return I2C error code
    */
    uint8_t writeRegister(uint8_t reg, uint8_t value);

    /*!
        @brief Read 1 byte from a register. Currently Not implemented due to IC's non-standard read protocol.
        @param reg Register to read
        @return Register value
    */
    uint8_t readRegister(uint8_t reg);

    /*!
        @brief Set channel current. Value maps 0.125mA to 24mA in 192 steps.
        @param channel Channel to set the current for
        @param value current value
        @return I2C error
    */
    uint8_t setChannelCurrent(Channel channel, uint8_t value);

    /*!
        @brief Set the mode of indivual channels. Must call sendChannelMode separately to update IC
        @param channel Led channel
        @param mode Choose an option from the 4 Led modes
        @return True is successful
    */
    bool updateChannelMode(Channel channel, LedMode mode);

    /*!
        @brief Write updated chanel modes to the IC
        @return I2C error
    */

    /*!
        @brief Read the contents of the Channel Control register
        @return Contents of the channel mode register
    */
    uint8_t getChannelControl();
    
    /*!
        @brief Write the Channel control register to the IC
        @return I2C error code
    */
    uint8_t sendChannelControl();
};
