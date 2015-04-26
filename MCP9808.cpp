//To do: Change write() to write one register at a time.

#include <MCP9808.h>
#include <Streaming.h>    //http://arduiniana.org/libraries/streaming/

//instantiate a temperature sensor object given the least three significant
//bits (A2:0) of its I2C address (0-7)
MCP9808::MCP9808(uint8_t LS_ADDR_BITS)
{
    _devAddr = MCP9808_BASE_ADDR | (LS_ADDR_BITS & 7);
}

//initialize
void MCP9808::begin(twiClockFreq_t twiFreq)
{
    Wire.begin();
    TWBR = ( (F_CPU / twiFreq) - 16) / 2;
    read();
}

//read all registers from the sensor.
//device does not support sequential access, so must read one register at a time :-|
//returns the I2C status (zero if successful). 
uint8_t MCP9808::read(void)
{
    uint8_t regs[SIZEOF_REGS];      //temporary storage for register data
    uint8_t* rp = regs;
    uint8_t e = 0;

    //first seven registers are two bytes each
    for (uint8_t r = CONFIG_REG; r < N_REGS; ++r)
    {
        Wire.beginTransmission(_devAddr);
        Wire.write(r);
        if ( (e = Wire.endTransmission()) != 0 ) return e;
        Wire.requestFrom(_devAddr, (uint8_t)2);
        *rp++ = Wire.read();
        *rp++ = Wire.read();
    }

    //last register is one byte
    Wire.beginTransmission(_devAddr);
    Wire.write(RESOLUTION_REG);
    if ( (e = Wire.endTransmission()) != 0 ) return e;
    Wire.endTransmission();
    Wire.requestFrom(_devAddr, (uint8_t)1);
    *rp = Wire.read();
    
    //assign to class members
    config = ( regs[0] << 8 ) + regs[1];
    tUpper    = ( ( regs[2] << 11 ) + ( regs[3] << 3 ) ) >> 5;
    tLower    = ( ( regs[4] << 11 ) + ( regs[5] << 3 ) ) >> 5;
    tCritical = ( ( regs[6] << 11 ) + ( regs[7] << 3 ) ) >> 5;
    tAmbient  = ( ( regs[8] << 11 ) + ( regs[9] << 3 ) ) >> 3;
    alertCritical = regs[8] & ALT_CRIT;
    alertUpper    = regs[8] & ALT_UPPER;
    alertLower    = regs[8] & ALT_LOWER;
    mfrID = ( regs[10] << 8 ) + regs[11];
    deviceID = regs[12];
    deviceRev = regs[13];
    resolution = regs[14];

    return e;
}

//write config, temperature and resolution registers (others are read-only)
//device does not support sequential access, so must write one register at a time :-|
//returns the I2C status (zero if successful). 
uint8_t MCP9808::write(void)
{
    uint8_t e = 0;

    //config and temperature registers
    Wire.beginTransmission(_devAddr);
    Wire.write( CONFIG_REG );
    Wire.write( config >> 8 );
    Wire.write( config & 0xFF );
    Wire.write( tUpper >> 11 );
    Wire.write( (tUpper << 2) & 0xFF );
    Wire.write( tLower >> 11 );
    Wire.write( (tLower << 2) & 0xFF );
    Wire.write( tCritical >> 11 );
    Wire.write( (tCritical << 2) & 0xFF );
    if ( (e = Wire.endTransmission()) != 0 ) return e;
    
    //resolution register
    Wire.beginTransmission(_devAddr);
    Wire.write( RESOLUTION_REG );
    Wire.write( resolution );
    return Wire.endTransmission();
}
