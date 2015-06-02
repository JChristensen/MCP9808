# Arduino Library for Microchip MCP9808 Maximum Accuracy Digital Temperature Sensor #
https://github.com/JChristensen/MCP9808
ReadMe file  
Jack Christensen Jun 2015

![CC BY-SA](http://mirrors.creativecommons.org/presskit/buttons/80x15/png/by-sa.png)

## Introduction ##
**Arduino Library for Microchip MCP9808 Maximum Accuracy Digital Temperature Sensor**

A lightweight implementation that exposes all functionality of the [Microchip MCP9808 sensor](http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en020949). Temperatures are handled in the integer domain to avoid the code size and runtime overhead associated with floating-point. Should the user wish to work in floating-point format, conversion is easily done in the application code.

The ambient temperature is read as °C\*16. If a lower resolution is configured, the applicable low-order bits are returned as zeroes.

The Upper, Lower and Critical temperature limit registers are read and written as °C\*4.

Bit masks for the config register are provided in the **MCP9808.h** file.  

"Arduino Library for Microchip MCP9808 Temperature Sensor" by Jack Christensen is licensed under [CC BY-SA 4.0](http://creativecommons.org/licenses/by-sa/4.0/).


## Installation ##
To use the **MCP9808** library:  
- Go to https://github.com/JChristensen/MCP9808, click the **Download ZIP** button and save the ZIP file to a convenient location on your PC.
- Uncompress the downloaded file.  This will result in a folder containing all the files for the library, that has a name that includes the branch name, usually **MCP9808-master**.
- Rename the folder to just **MCP9808**.
- Copy the renamed folder to the Arduino sketchbook\libraries folder.

## Examples ##
The following example sketch is included with the **MCP9808** library:
- **MCP9808_EX1:** Demonstrates basic reading of ambient temperature in Celsius and Fahrenheit, conversion to floating-point, changing device options via the Cofiguration register, and changing the Limit-Set and Hysteresis registers.

## Usage notes ##
The **MCP9808** library is designed for use with Arduino version 1.0 or later.

To use the **MCP9808** library, the standard Arduino Wire library must also be included.  For brevity, this include is not repeated in the examples below:
```c++
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)
```
## Enumeration ##

###twiClockFreq_t
#####Description
Symbolic names for I2C bus speeds.
#####Values
- **twiClock100kHz** -- 100kHz bus speed.  
- **twiClock400kHz** -- 400kHz bus speed.  

## Constructor ##

###MCP9808(uint8_t LS_ADDR_BITS)
#####Description
Instantiates an MCP9808 sensor object.
#####Syntax
`MCP9808 mySensor(0);`
#####Parameters
**LS_ADDR_BITS:** An integer *(uint8_t)* representing the least-significant three bits of the I2C device address (i.e. a value between 0 and 7).

## Methods ##
###begin(twiClockFreq_t twiFreq)
#####Description
Initializes the library. Calling begin() calls read() to initially populate the sensor data into local storage. Call this method once in the setup code.
#####Syntax
`mySensor.begin(twiClock400kHz);`
#####Parameters
**twiFreq:** An optional parameter specifying the speed for the I2C bus. If omitted, it defaults to 100kHz *(twiClockFreq_t)*
#####Returns
I2C status (zero if successful) *(uint8_t)*.
#####Example
```c++
MCP9808 mySensor(0);
mySensor.begin(twiClock400kHz);
```
###read(void)
#####Description
Reads data from the sensor into local storage. See Properties below for a description of the data.
#####Syntax
`mySensor.read();`
#####Parameters
None.
#####Returns
I2C status (zero if successful) *(uint8_t)*.
#####Example
```c++
MCP9808 mySensor(0);
mySensor.begin();
uint8_t e = mySensor.read();
if ( e != 0 )
{
	//there was an error on the bus
}
else
{
	//all is well
}
```
###write(void)
#####Description
Writes data from local storage to the sensor. Note that only the three critical temperature registers, the configuration register, and the resolution register are written, other registers are read-only.
#####Syntax
`mySensor.write();`
#####Parameters
None.
#####Returns
I2C status (zero if successful) *(uint8_t)*.
#####Example
```c++
MCP9808 mySensor(0);
mySensor.begin();
mySensor.tUpper = 100;    //set upper limit to 25C (77F)
mySensor.write();
```

## Properties ##
**tUpper:** Upper temperature limit, in units of °C\*4. _(int16\_t)_
**tLower:** Lower temperature limit, in units of °C\*4. _(int16\_t)_
**tCritical:** Critical temperature limit, in units of °C\*4. *(int16\_t)*
**tAmbient:** Ambient temperature, in units of °C\*16. Read-only. *(int16\_t)*
**config:** Configuration register, see datasheet for details. *(uint16\_t)*
**resolution:** Temperature resolution for the ambient temperature. An integer between 0 and 3, where 0 is ±0.5°C, 1 is ±0.25°C, 2 is ±0.125°C, and 3 is ±0.0625°C. Higher resolutions require longer conversion times, see the datasheet. ±0.0625°C is the power-on default. *(uint8\_t)*
**alertCritical:** If tAmbient ≥ tCritical, then *true*, else *false*. Read-only. *(bool)*
**alertUpper:** If tAmbient > tUpper, then *true*, else *false*. Read-only. *(bool)*
**alertLower:** If tAmbient < tLower, then *true*, else *false*. Read-only. *(bool)*
**mfrID:** Manufacturer ID. Read-only. *(uint16\_t)*
**deviceID:** Device ID. Read-only. *(uint8\_t)*
**deviceRev:** Device revision. Read-only. *(uint8\_t)*
