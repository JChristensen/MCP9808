# Arduino MCP9808 Temperature Sensor Library v1.0 #
https://github.com/JChristensen/MCP9808
ReadMe file  
Jack Christensen Apr 2015

![CC BY-SA](http://mirrors.creativecommons.org/presskit/buttons/80x15/png/by-sa.png)

## Introduction ##
**Arduino Library for Microchip MCP9808 Maximum Accuracy Digital Temperature Sensor**

A lightweight implementation that exposes all functionality of the [Microchip MCP9808 sensor](http://www.microchip.com/wwwproducts/Devices.aspx?dDocName=en020949). Temperatures are handled in the integer domain to avoid the code size and runtime overhead associated with floating-point. Still, it is easy enough to perform the necessary conversions should the user wish to work in floating-point format.

Temperatures read from the device's registers are returned as °C\*16. (If the device resolution is set to less than 12 bits, the corresponding lower order bits are simply returned as zero.) Temperatures can alternately be read as °F\*10.

When writing the Hysteresis and Limit-Set registers, the value must be given as °C*2, which corresponds to the internal representation in these registers.

Bit masks for the control register are provided in the **MCP980X.h** file.     

"Arduino Library for Microchip MCP9808" by Jack Christensen is licensed under [CC BY-SA 4.0](http://creativecommons.org/licenses/by-sa/4.0/).


## Installation ##
To use the **MCP980X** library:  
- Go to https://github.com/JChristensen/MCP980X, click the **Download ZIP** button and save the ZIP file to a convenient location on your PC.
- Uncompress the downloaded file.  This will result in a folder containing all the files for the library, that has a name that includes the branch name, usually **MCP980X-master**.
- Rename the folder to just **MCP980X**.
- Copy the renamed folder to the Arduino sketchbook\libraries folder.

## Examples ##
The following example sketch is included with the **MCP980X** library:
- **MCP980X_EX1:** Demonstrates basic reading of ambient temperature in Celsius and Fahrenheit, conversion to floating-point, changing device options via the Cofiguration register, and changing the Limit-Set and Hysteresis registers.

## Usage notes ##
The **MCP980X** library is designed for use with Arduino version 1.0 or later.

To use the **MCP980X** library, the standard Arduino Wire library must also be included.  For brevity, this include is not repeated in the examples below:
```c++
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)
```
## Enumeration ##

###MCP980X_REGS_t
#####Description
Symbolic names for the MCP980X registers.
#####Values
- AMBIENT -- for the Ambient Temperature Register  
- HYSTERESIS -- for the Temperature Hysteresis Register  
- LIMITSET -- for the Temperature Limit-Set Register

## Constructor ##

###MCP980X(int LS_ADDR_BITS)
#####Description
Instantiates an MCP980X sensor object.
#####Syntax
`MCP980X mySensor(0);`
#####Parameters
**LS_ADDR_BITS:** An integer *(int)* representing the least-significant three bits of the I2C device address (i.e. a value between 0 and 7). Note that some devices in the MCP980X family allow the user to select the least significant three bits of the address, and some have a fixed address from the factory. See the datasheet for details. As ever, all devices on an I2C bus must have unique addresses.

## Methods ##
###begin(void)
#####Description
Initializes the library. Call this method once in the setup code.
#####Syntax
`mySensor.begin(void);`
#####Parameters
None.
#####Returns
None.
#####Example
```c++
MCP980X mySensor(0);
mySensor.begin();
```
###readTempC16(MCP980X_REGS_t reg)
#####Description
Reads one of the three temperature registers from the sensor.
#####Syntax
`mySensor.readTempC16(MCP980X_REGS_t reg);`
#####Parameters
**reg:** The temperature register to read, AMBIENT, HYSTERESIS or LIMITSET *(MCP980X_REGS_t)*
#####Returns
Temperature as degrees Celsius times 16 *(int)*.
#####Example
```c++
MCP980X mySensor(0);
mySensor.begin();
int c16 = mySensor.readTempC16(AMBIENT);
float C = c16 / 16.0;
```
###readTempF10(MCP980X_REGS_t reg)
#####Description
Reads one of the three temperature registers from the sensor.
#####Syntax
`mySensor.readTempF10(MCP980X_REGS_t reg);`
#####Parameters
**reg:** The temperature register to read, AMBIENT, HYSTERESIS or LIMITSET *(MCP980X_REGS_t)*
#####Returns
Temperature as degrees Fahrenheit times 10 *(int)*.
#####Example
```c++
MCP980X mySensor(0);
mySensor.begin();
int f10 = mySensor.readTempF10(AMBIENT);
float F = f10 / 10.0;
```
###writeTempC2(MCP980X_REGS_t reg, int value)
#####Description
Sets the Temperature Hysteresis Register or the Temperature Limit-Set Register.
#####Syntax
`mySensor.writeTempC2(MCP980X_REGS_t reg, int value);`
#####Parameters
**reg:** The temperature register to write, HYSTERESIS or LIMITSET *(MCP980X_REGS_t)*. If given the AMBIENT temperature register, no action is taken (AMBIENT is a read-only register).  
**value:** The temperature value to set, in degrees Celsius times two *(int)*
#####Returns
None.
#####Example
```c++
MCP980X mySensor(0);
mySensor.begin();
mySensor.writeTempC2(HYSTERESIS, 25 * 2);	//set hysteresis register to 25°C
mySensor.writeTempC2(LIMITSET, 100 * 2);	//set limit-set register to 100°C
```
###readConfig(void)
#####Description
Reads the value of the configuration register.
#####Syntax
`mySensor.readConfig(void);`
#####Parameters
None.
#####Returns
Configuration register value *(byte)*
#####Example
```c++
MCP980X mySensor(0);
mySensor.begin();
byte config = mySensor.readConfig();
```
###writeConfig(uint8_t value)
#####Description
Writes a value to the configuration register.
#####Syntax
`mySensor.writeConfig(byte value);`
#####Parameters
**value:** The value to be written to the register. See the MCP980X.h file for symbolic definitions for the bits in the configuration register.
#####Returns
None.
#####Example
```c++
MCP980X mySensor(0);
mySensor.begin();
//set ADC resolution to 12 bits and the fault queue length to 6
byte config = ADC_RES_12BITS | FAULT_QUEUE_6;
mySensor.writeConfig(config);
```
