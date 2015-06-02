//Arduino Library for Microchip MCP9808 Temperature Sensor.
//Example sketch.
//Prints the initial register values, then changes the limit registers,
//then prints the register values every two seconds.
//Jack Christensen Jun 2015

#include <MCP9808.h>      //http://github.com/JChristensen/MCP9808
#include <Streaming.h>    //http://arduiniana.org/libraries/streaming/
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire

MCP9808 mySensor(0);

void setup(void)
{
    Serial.begin(9600);
    Serial << F( "\n" __FILE__ " " __DATE__ " " __TIME__ "\n" );

    delay(500);                         //time for the sensor to perform an initial temperature conversion
    uint8_t status = mySensor.begin();  //initialize the hardware
    if ( status != 0 )
    {
        Serial << "Error reading sensor, status=" << status << endl;
        Serial.flush();
        while (1);                      //loop until reset
    }
    displayData();                      //print the initial sensor data
    mySensor.tUpper = 100;              //25C (77F)
    mySensor.tLower = -40;              //-10C (14F)
    mySensor.tCritical = 120;           //30C (86F)
    mySensor.write();                   //write the changed values
}

void loop(void)
{
    delay(2000);
    displayData();
}

//print the data from the sensor on the serial monitor
void displayData(void)
{
    float C, F;
    uint8_t status;
    
    if ( (status = mySensor.read()) == 0 )
    {
        C = mySensor.tUpper / 16.0;
        F = C * 9.0 / 5.0 + 32.0;
        Serial << F("\nUpper Limit\t") << C << F("C\t") << F << F("F\tAlert=") << mySensor.alertUpper << endl;
        C = mySensor.tLower / 16.0;
        F = C * 9.0 / 5.0 + 32.0;
        Serial << F("Lower Limit\t") << C << F("C\t") << F << F("F\tAlert=") << mySensor.alertLower << endl;
        C = mySensor.tCritical / 16.0;
        F = C * 9.0 / 5.0 + 32.0;
        Serial << F("Critical Limit\t") << C << F("C\t") << F << F("F\tAlert=") << mySensor.alertCritical << endl;
        C = mySensor.tAmbient / 16.0;
        F = C * 9.0 / 5.0 + 32.0;
        Serial << F("Ambient\t\t") << C << F("C\t") << F << F("F\n");
        Serial << F("Config 0x") << _HEX(mySensor.config) << F(" Resolution 0x") << _HEX(mySensor.resolution) << endl;
        Serial << F("Mfr ID 0x") << _HEX(mySensor.mfrID) << F( " Device ID 0x") << _HEX(mySensor.deviceID) << F( " Device Rev 0x") << _HEX(mySensor.deviceRev) << endl;
        
    }
    else
    {
        Serial << "Error reading sensor, status=" << status << endl;
    }
}

