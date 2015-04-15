/*-----------------------------------------------------------------------------*
 * Arduino Library for Microchip MCP9800/1/2/3 2-Wire High-Accuracy            *
 * Temperature Sensors                                                         *
 *                                                                             *
 * A lightweight implementation that exposes all functionality of the MCP980X  *
 * sensors. Temperatures are dealt with in the integer domain to avoid         *
 * the code size and runtime overhead associated with floating-point. Still,   *
 * it is easy enough to perform the necessary conversions should the user      *
 * wish to work in floating-point format.                                      *
 *                                                                             *
 * Temperatures read from the device's registers are returned as °C*16.        *
 * (If the device resolution is set to less than 12 bits, the corresponding    *
 * lower order bits are simply returned as zero.) Temperatures can             *
 * alternately be read as °F*10.                                               *
 *                                                                             *
 * When writing the Hysteresis and Limit-Set registers, the value must be      *
 * given as °C*2, which corresponds to the internal representation in these    *
 * registers.                                                                  *
 *                                                                             *
 * Bit masks for the control register are provided in the MCP980X.h file.      *
 *                                                                             *
 * Jack Christensen 21Mar2014 v1.0                                             *
 *                                                                             *
 * "Arduino library for Microchip MCP9800/1/2/3" by Jack Christensen           *
 * is licensed under CC BY-SA 4.0,                                             *
 * http://creativecommons.org/licenses/by-sa/4.0/                              *
 *-----------------------------------------------------------------------------*/

#ifndef _MCP980X_H
#define _MCP980X_H

#include <Arduino.h>
#include <Wire.h>

const int MCP980X_BASE_ADDR = 0x18;

//register addresses
enum MCP980X_REGS_t { AMBIENT = 0, HYSTERESIS = 2, LIMITSET = 3 };
const uint8_t CONFIG_REG = 1;

//bit definitions for config register
const uint8_t ONE_SHOT = 0x80;
const uint8_t ADC_RES_9BITS = 0x00;
const uint8_t ADC_RES_10BITS = 0x20;
const uint8_t ADC_RES_11BITS = 0x40;
const uint8_t ADC_RES_12BITS = 0x60;
const uint8_t FAULT_QUEUE_1 = 0x00;
const uint8_t FAULT_QUEUE_2 = 0x08;
const uint8_t FAULT_QUEUE_4 = 0x10;
const uint8_t FAULT_QUEUE_6 = 0x18;
const uint8_t ALERT_POLARITY_HIGH = 0x04;
const uint8_t INTERRUPT_MODE = 0x02;
const uint8_t SHUTDOWN = 0x01;

class MCP980X
{
    public:
        MCP980X(uint8_t LS_ADDR_BITS);
        void begin(void);
        int readTempC16(MCP980X_REGS_t reg);
        int readTempF10(MCP980X_REGS_t reg);
        void writeTempC2(MCP980X_REGS_t reg, int value);
        uint8_t readConfig(void);
        void writeConfig(uint8_t value);

    private:
        uint8_t _devAddr;
};
#endif
