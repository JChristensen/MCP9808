/*-----------------------------------------------------------------------------*
 * Arduino Library for Microchip MCP9808 Maximum Accuracy Digital              *
 * Temperature Sensor                                                          *
 *                                                                             *
 * A lightweight implementation that exposes all functionality of the MCP9808  *
 * sensor.  Temperatures are handled in the integer domain to avoid            *
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
 * Bit masks for the control register are provided in the MCP9808.h file.      *
 *                                                                             *
 * Jack Christensen 15Apr2015 v1.0                                             *
 *                                                                             *
 * "Arduino library for Microchip MCP9808" by Jack Christensen                 *
 * is licensed under CC BY-SA 4.0,                                             *
 * http://creativecommons.org/licenses/by-sa/4.0/                              *
 *-----------------------------------------------------------------------------*/

#ifndef _MCP9808_H
#define _MCP9808_H

#include <Arduino.h>
#include <Wire.h>

const int MCP9808_BASE_ADDR(0x18);

//register addresses
const uint8_t     CONFIG_REG(0x01);
const uint8_t     tUPPER_REG(0x02);
const uint8_t     tLOWER_REG(0x03);
const uint8_t  tCRITICAL_REG(0x04);
const uint8_t   tAMBIENT_REG(0x05);
const uint8_t     MFR_ID_REG(0x06);
const uint8_t     DVC_ID_REG(0x07);
const uint8_t RESOLUTION_REG(0x08);

const uint8_t N_REGS(8);        //eight registers
const uint8_t SIZEOF_REGS(15);  //the eight registers comprise 15 bytes,
                                //two bytes each except RESOLUTION_REG is one byte

//bit definitions for config register
const uint16_t HYSTERESIS(0x0600);
const uint16_t       SHDN(0x0100);
const uint16_t    CRT_LOC(0x0080);
const uint16_t    WIN_LOC(0x0040);
const uint16_t    INT_CLR(0x0020);
const uint16_t   ALT_STAT(0x0010);
const uint16_t    ALT_CNT(0x0080);
const uint16_t    ALT_SEL(0x0040);
const uint16_t    ALT_POL(0x0020);
const uint16_t    ALT_MOD(0x0010);

//bit definitions for ambient temperature register MSB
const uint8_t  ALT_CRIT(0x80);
const uint8_t ALT_UPPER(0x40);
const uint8_t ALT_LOWER(0x20);

//I2C clock frequencies
enum twiClockFreq_t { twiClock100kHz = 100000, twiClock400kHz = 400000 };

class MCP9808
{
    public:
        MCP9808(uint8_t LS_ADDR_BITS);
        void
            begin(twiClockFreq_t twiFreq = twiClock100kHz);

        uint8_t
            read(void),
            write(void);
        
        int16_t
            tUpper,         //upper temperature limit, in units of 1/4 °C
            tLower,         //lower temperature limit, in units of 1/4 °C
            tCritical,      //critical temperature limit, in units of 1/4 °C
            tAmbient;       //ambient temperature, in units of 1/16 °C

        uint16_t
            config,
            mfrID;
            
        uint8_t
            deviceID,
            deviceRev,
            resolution;
            
        bool
            alertCritical,
            alertUpper,
            alertLower;

    private:
        uint8_t
            _devAddr;
};
#endif
