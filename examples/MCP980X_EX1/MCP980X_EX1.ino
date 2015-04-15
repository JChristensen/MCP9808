#include <MCP980X.h>      //http://github.com/JChristensen/MCP980X
#include <Streaming.h>    //http://arduiniana.org/libraries/streaming/
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire

MCP980X mySensor(0);

void setup(void)
{
    Serial.begin(115200);
    delay(1000);
    Serial << endl;

    mySensor.begin();        //initialize the hardware
    displayRegs();           //print the initial register values

    mySensor.writeConfig(ADC_RES_12BITS);       //max resolution, 0.0625 °C
    mySensor.writeTempC2(HYSTERESIS, 0 * 2);    //freezing
    mySensor.writeTempC2(LIMITSET, 100 * 2);    //boiling
}

void loop(void)
{
    delay(2000);
    displayRegs();
}

//print the values of all four registers on the serial monitor
void displayRegs(void)
{
    float C, F;
    
    uint8_t config = mySensor.readConfig();
    C = mySensor.readTempC16(AMBIENT) / 16.0;
    F = mySensor.readTempF10(AMBIENT) / 10.0;
    Serial << F("Config=") << (config < 16 ? F("0x0") : F("0x")) << _HEX(config) << F(", Ambient ") << C << F("C ") << F << 'F';
    
    C = mySensor.readTempC16(HYSTERESIS) / 16.0;
    F = mySensor.readTempF10(HYSTERESIS) / 10.0;
    Serial << F(", Hysteresis ") << C << F("C ") << F << 'F';

    C = mySensor.readTempC16(LIMITSET) / 16.0;
    F = mySensor.readTempF10(LIMITSET) / 10.0;
    Serial << F(", Limit-Set ") << C << F("C ") << F << 'F' << endl;
}

