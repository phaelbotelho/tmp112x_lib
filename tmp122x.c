/* 
 * File:   tmp122x.c
 * Author: Raphael
 *
 * Created on October 22, 2019, 11:06 AM
 */

#include "tmp122x.h"
#include "my_i2c.h"

void TMP112x_Init()
{
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(0x01); // Select configuration register
    I2C_WriteByte(0x60); // Continuous conversion, comparator mode, 12-bit resolution
    I2C_WriteByte(0xA0);
    I2C_Stop(); // Stop I2C Transmission
}

float TMP112x_ReadTemp()
{
    uint8_t _temp_lo = 0;
    uint8_t _temp_hi = 0;
    int16_t digitalTemp = 0;

    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(TEMPERATURE_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    _temp_hi = I2C_ReadByte(1); // Read the data
    _temp_lo = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission
    
    // Bit 0 of second byte will always be 0 in 12-bit readings and 1 in 13-bit
    if(_temp_lo & 0x01) // 13 bit mode
    {
        // Combine bytes to create a signed int
        digitalTemp = ((_temp_hi) << 5) | (_temp_lo >> 3);
        // Temperature data can be + or -, if it should be negative,
        // convert 13 bit to 16 bit and use the 2s compliment.
        if(digitalTemp > 0xFFF)
        {
            digitalTemp |= 0xE000;
        }
    }
    else // 12 bit mode
    {
        // Combine bytes to create a signed int 
        digitalTemp = ((_temp_hi) << 4) | (_temp_lo >> 4);
        // Temperature data can be + or -, if it should be negative,
        // convert 12 bit to 16 bit and use the 2s compliment.
        if(digitalTemp > 0x7FF)
        {
            digitalTemp |= 0xF000;
        }
    }
   
   return digitalTemp * 0.0625;
   //return ((digitalTemp * 0.0625) * 1.8 + 32);
}

void TMP112x_SetConversionRate(uint8_t rate)
{
    uint8_t registerByte[2]; // Store the data from the register here
    rate = rate&0x03; // Make sure rate is not set higher than 3.
  
    // Change pointer address to configuration register (0x01)
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte[0] = I2C_ReadByte(1); // Read the data
    registerByte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission

    // Load new conversion rate
    registerByte[1] &= 0x3F;  // Clear CR0/1 (bit 6 and 7 of second byte)
    registerByte[1] |= rate<<6;	// Shift in new conversion rate

    // Set configuration registers
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_WriteByte(registerByte[0]); // Write second byte
    I2C_WriteByte(registerByte[1]); // Select data register
    I2C_Stop(); // Stop I2C Transmission
}


void TMP112x_SetExtendedMode(bool mode) 
{
    uint8_t registerByte[2]; // Store the data from the register here

    // Change pointer address to configuration register (0x01)
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte[0] = I2C_ReadByte(1); // Read the data
    registerByte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission

    // Load new value for extention mode
    registerByte[1] &= 0xEF;		// Clear EM (bit 4 of second byte)
    registerByte[1] |= mode<<4;	// Shift in new exentended mode bit

    // Set configuration registers
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_WriteByte(registerByte[0]); // Write second byte
    I2C_WriteByte(registerByte[1]); // Select data register
    I2C_Stop(); // Stop I2C Transmission
}


void TMP112x_Sleep(void)
{
    uint8_t registerByte; // Store the data from the register here

    // Change pointer address to configuration register (0x01)
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission
  
    registerByte |= 0x01;	// Set SD (bit 0 of first byte)

    // Set configuration register
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_WriteByte(registerByte); // Write first byte
    I2C_Stop(); // Stop I2C Transmission
}


void TMP112x_Wakeup(void)
{
    uint8_t registerByte; // Store the data from the register here

    // Change pointer address to configuration register (0x01)
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission

    registerByte &= 0xFE;	// Clear SD (bit 0 of first byte)

    // Set configuration register
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_WriteByte(registerByte); // Write first byte
    I2C_Stop(); // Stop I2C Transmission
}


void TMP112x_SetAlertPolarity(bool polarity)
{
    uint8_t registerByte; // Store the data from the register here

    // Change pointer address to configuration register (0x01)
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission

    // Load new value for polarity
    registerByte &= 0xFB; // Clear POL (bit 2 of registerByte)
    registerByte |= polarity<<2;  // Shift in new POL bit

    // Set configuration register
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_WriteByte(registerByte); // Write first byte
    I2C_Stop(); // Stop I2C Transmission
}


bool TMP112x_Alert(void)
{
  uint8_t registerByte; // Store the data from the register here

    // Change pointer address to configuration register (0x01)
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission
  
    registerByte &= 0x20;	// Clear everything but the alert bit (bit 5)
    return registerByte>>5;
}


void TMP112x_SetLowTempC(float temperature)
{
  uint8_t registerByte[2];	// Store the data from the register here
  bool extendedMode;	// Store extended mode bit here 0:-55C to +128C, 1:-55C to +150C
  
  // Prevent temperature from exceeding 150C or -55C
  if(temperature > 150.0f)
  {
    temperature = 150.0f;
  }
  if(temperature < -55.0)
  {
    temperature = -55.0f;
  }
  
    //Check if temperature should be 12 or 13 bits
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte[0] = I2C_ReadByte(1); // Read the data
    registerByte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission
    
    extendedMode = (registerByte[1]&0x10) >> 4;	// 0 - temp data will be 12 bits
                                                // 1 - temp data will be 13 bits
  
    // Convert analog temperature to digital value
    temperature = temperature/0.0625;
  
    // Split temperature into separate bytes
    if(extendedMode)	// 13-bit mode
    {
        //registerByte[0] = int(temperature) >> 5;
        //registerByte[1] = (int(temperature) << 3);
    }
    else	// 12-bit mode
    {
        //registerByte[0] = int(temperature) >> 4;
        //registerByte[1] = int(temperature) << 4;
    }
  
    // Write to T_LOW Register
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(T_LOW_REGISTER); // Point to T_LOW
    I2C_WriteByte(registerByte[0]); // Write second byte
    I2C_WriteByte(registerByte[1]); // Select data register
    I2C_Stop(); // Stop I2C Transmission
}


void TMP112x_SetHighTempC(float temperature)
{
  uint8_t registerByte[2];	// Store the data from the register here
  bool extendedMode;	// Store extended mode bit here 0:-55C to +128C, 1:-55C to +150C
  
  // Prevent temperature from exceeding 150C
  if(temperature > 150.0f)
  {
    temperature = 150.0f;
  }
  if(temperature < -55.0)
  {
    temperature = -55.0f;
  }
  
    // Check if temperature should be 12 or 13 bits
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte[0] = I2C_ReadByte(1); // Read the data
    registerByte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission
  
    extendedMode = (registerByte[1]&0x10)>>4;  // 0 - temp data will be 12 bits
                                               // 1 - temp data will be 13 bits

    // Convert analog temperature to digital value
    temperature = temperature/0.0625;
  
    // Split temperature into separate bytes
    if(extendedMode)	// 13-bit mode
    {
        //registerByte[0] = int(temperature) >> 5;
        //registerByte[1] = (int(temperature) << 3);
    }
    else	// 12-bit mode
    {
        //registerByte[0] = int(temperature) >> 4;
        //registerByte[1] = int(temperature) << 4;
    }
  
    // Write to T_HIGH Register
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(T_HIGH_REGISTER); 	// Point to T_HIGH register
    I2C_WriteByte(registerByte[0]); // Write second byte
    I2C_WriteByte(registerByte[1]); // Select data register
    I2C_Stop(); // Stop I2C Transmission
}


void TMP112x_SetLowTempF(float temperature)
{
  temperature = (temperature - 32)*5/9; // Convert temperature to C
  TMP112x_SetLowTempC(temperature); // Set T_LOW
}


void TMP112x_SetHighTempF(float temperature)
{
  temperature = (temperature - 32)*5/9; // Convert temperature to C
  TMP112x_SetHighTempC(temperature); // Set T_HIGH
}


float TMP112x_ReadLowTempC(void)
{
  uint8_t registerByte[2];	// Store the data from the register here
  bool extendedMode;	// Store extended mode bit here 0:-55C to +128C, 1:-55C to +150C
  int16_t digitalTemp;		// Store the digital temperature value here
  float temperature;	// Store the analog temperature value here
  
    // Check if temperature should be 12 or 13 bits
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte[0] = I2C_ReadByte(1); // Read the data
    registerByte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission
  
    extendedMode = (registerByte[1]&0x10) >> 4;  // 0 - temp data will be 12 bits
                                               // 1 - temp data will be 13 bits
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(T_LOW_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte[0] = I2C_ReadByte(1); // Read the data
    registerByte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission
  
  if(extendedMode)	// 13 bit mode
  {
	// Combine bytes to create a signed int
    digitalTemp = ((registerByte[0]) << 5) | (registerByte[1] >> 3);
	// Temperature data can be + or -, if it should be negative,
	// convert 13 bit to 16 bit and use the 2s compliment.
    if(digitalTemp > 0xFFF)
	{
      digitalTemp |= 0xE000;
    }
  }
  else	// 12 bit mode
  {
	// Combine bytes to create a signed int 
    digitalTemp = ((registerByte[0]) << 4) | (registerByte[1] >> 4);
	// Temperature data can be + or -, if it should be negative,
	// convert 12 bit to 16 bit and use the 2s compliment.
    if(digitalTemp > 0x7FF)
	{
      digitalTemp |= 0xF000;
    }
  }
  // Convert digital reading to analog temperature (1-bit is equal to 0.0625 C)
  return digitalTemp*0.0625;
}


float TMP112x_ReadHighTempC(void)
{
  uint8_t registerByte[2];	// Store the data from the register here
  bool extendedMode;	// Store extended mode bit here 0:-55C to +128C, 1:-55C to +150C
  int16_t digitalTemp;		// Store the digital temperature value here
  float temperature;	// Store the analog temperature value here
  
    // Check if temperature should be 12 or 13 bits
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte[0] = I2C_ReadByte(1); // Read the data
    registerByte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission
    
    extendedMode = (registerByte[1]&0x10) >> 4;	// 0 - temp data will be 12 bits
											// 1 - temp data will be 13 bits
    
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(T_HIGH_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte[0] = I2C_ReadByte(1); // Read the data
    registerByte[1] = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission
  
  if(extendedMode)	// 13 bit mode
  {
	// Combine bytes to create a signed int
    digitalTemp = ((registerByte[0]) << 5) | (registerByte[1] >> 3);
	// Temperature data can be + or -, if it should be negative,
	// convert 13 bit to 16 bit and use the 2s compliment.
    if(digitalTemp > 0xFFF)
	{
      digitalTemp |= 0xE000;
    }
  }
  else	// 12 bit mode
  {
	// Combine bytes to create a signed int 
    digitalTemp = ((registerByte[0]) << 4) | (registerByte[1] >> 4);
	// Temperature data can be + or -, if it should be negative,
	// convert 12 bit to 16 bit and use the 2s compliment.
    if(digitalTemp > 0x7FF)
	{
      digitalTemp |= 0xF000;
    }
  }
  
  // Convert digital reading to analog temperature (1-bit is equal to 0.0625 C)
  return digitalTemp * 0.0625;
}


float TMP112x_ReadLowTempF(void)
{
  return TMP112x_ReadLowTempC() * 1.8 + 32.0;
}


float TMP112x_ReadHighTempF(void)
{
  return TMP112x_ReadHighTempC() * 1.8 + 32.0;
}


void TMP112x_SetFault(uint8_t faultSetting)
{
    uint8_t registerByte; // Store the data from the register here

    faultSetting = faultSetting&3; // Make sure rate is not set higher than 3.
  
    // Change pointer address to configuration register (0x01)
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission
    
    // Load new conversion rate
    registerByte &= 0xE7;  // Clear F0/1 (bit 3 and 4 of first byte)
    registerByte |= faultSetting << 3;	// Shift new fault setting

    // Set configuration register
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_WriteByte(registerByte); // Write first byte
    I2C_Stop(); // Stop I2C Transmission
}


void TMP112x_SetAlertMode(bool mode)
{
  uint8_t registerByte; // Store the data from the register here
  
    // Change pointer address to configuration register (1)
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_RepeatedStart(); // Repeat Start I2C Transmission Condition.
    I2C_WriteByte(TMP112x_ADR + 1); // Send the ADR to the talk device.
    registerByte = I2C_ReadByte(0); // Read the data
    I2C_Stop(); // Stop I2C Transmission
    
    // Load new conversion rate
    registerByte &= 0xFD;	// Clear old TM bit (bit 1 of first byte)
    registerByte |= mode << 1;	// Shift in new TM bit
    
    // Set configuration register
    I2C_Start(); // Start I2C Transmission
    I2C_WriteByte(TMP112x_ADR); // Send the ADR to the talk device.
    I2C_WriteByte(CONFIG_REGISTER); // Select data register
    I2C_WriteByte(registerByte); // Write first byte
    I2C_Stop(); // Stop I2C Transmission
}