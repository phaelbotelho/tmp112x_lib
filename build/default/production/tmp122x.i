# 1 "tmp122x.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "tmp122x.c" 2







# 1 "./tmp122x.h" 1
# 11 "./tmp122x.h"
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 1 3



# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 2 3
# 22 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 135 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uintptr_t;
# 150 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long intptr_t;
# 166 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef long int32_t;
# 189 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef int32_t intmax_t;







typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef unsigned long uint32_t;
# 225 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef uint32_t uintmax_t;
# 22 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 2 3


typedef int8_t int_fast8_t;




typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;




typedef uint8_t uint_fast8_t;




typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
# 131 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 131 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 2 3
# 11 "./tmp122x.h" 2

# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdbool.h" 1 3
# 12 "./tmp122x.h" 2
# 24 "./tmp122x.h"
void TMP112x_Init();

float TMP112x_ReadTemp();






void TMP112x_SetConversionRate(uint8_t rate);




void TMP112x_SetExtendedMode(_Bool mode);




void TMP112x_SetAlertPolarity(_Bool polarity);






void TMP112x_SetFault(uint8_t faultSetting);




void TMP112x_SetAlertMode(_Bool mode);
# 8 "tmp122x.c" 2

# 1 "./my_i2c.h" 1
# 14 "./my_i2c.h"
unsigned char I2C_ReadByte(unsigned char acknowledge);
unsigned char I2C_WriteByte(unsigned char data_out);

void I2C_Init(unsigned char clock_output);
void I2C_Start(void);
void I2C_RepeatedStart(void);
void I2C_Stop(void);
void I2C_Idle(void);
void I2C_Close(void);
# 9 "tmp122x.c" 2


void TMP112x_Init()
{
    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_WriteByte(0x60);
    I2C_WriteByte(0xA0);
    I2C_Stop();
}

float TMP112x_ReadTemp()
{
    uint8_t _temp_lo = 0;
    uint8_t _temp_hi = 0;
    int16_t digitalTemp = 0;

    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x00);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    _temp_hi = I2C_ReadByte(1);
    _temp_lo = I2C_ReadByte(0);
    I2C_Stop();


    if(_temp_lo & 0x01)
    {

        digitalTemp = ((_temp_hi) << 5) | (_temp_lo >> 3);


        if(digitalTemp > 0xFFF)
        {
            digitalTemp |= 0xE000;
        }
    }
    else
    {

        digitalTemp = ((_temp_hi) << 4) | (_temp_lo >> 4);


        if(digitalTemp > 0x7FF)
        {
            digitalTemp |= 0xF000;
        }
    }

   return digitalTemp * 0.0625;

}

void TMP112x_SetConversionRate(uint8_t rate)
{
    uint8_t registerByte[2];
    rate = rate&0x03;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte[0] = I2C_ReadByte(1);
    registerByte[1] = I2C_ReadByte(0);
    I2C_Stop();


    registerByte[1] &= 0x3F;
    registerByte[1] |= rate<<6;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_WriteByte(registerByte[0]);
    I2C_WriteByte(registerByte[1]);
    I2C_Stop();
}


void TMP112x_SetExtendedMode(_Bool mode)
{
    uint8_t registerByte[2];


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte[0] = I2C_ReadByte(1);
    registerByte[1] = I2C_ReadByte(0);
    I2C_Stop();


    registerByte[1] &= 0xEF;
    registerByte[1] |= mode<<4;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_WriteByte(registerByte[0]);
    I2C_WriteByte(registerByte[1]);
    I2C_Stop();
}


void TMP112x_Sleep(void)
{
    uint8_t registerByte;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte = I2C_ReadByte(0);
    I2C_Stop();

    registerByte |= 0x01;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_WriteByte(registerByte);
    I2C_Stop();
}


void TMP112x_Wakeup(void)
{
    uint8_t registerByte;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte = I2C_ReadByte(0);
    I2C_Stop();

    registerByte &= 0xFE;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_WriteByte(registerByte);
    I2C_Stop();
}


void TMP112x_SetAlertPolarity(_Bool polarity)
{
    uint8_t registerByte;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte = I2C_ReadByte(0);
    I2C_Stop();


    registerByte &= 0xFB;
    registerByte |= polarity<<2;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_WriteByte(registerByte);
    I2C_Stop();
}


_Bool TMP112x_Alert(void)
{
  uint8_t registerByte;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte = I2C_ReadByte(0);
    I2C_Stop();

    registerByte &= 0x20;
    return registerByte>>5;
}


void TMP112x_SetLowTempC(float temperature)
{
  uint8_t registerByte[2];
  _Bool extendedMode;


  if(temperature > 150.0f)
  {
    temperature = 150.0f;
  }
  if(temperature < -55.0)
  {
    temperature = -55.0f;
  }


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte[0] = I2C_ReadByte(1);
    registerByte[1] = I2C_ReadByte(0);
    I2C_Stop();

    extendedMode = (registerByte[1]&0x10) >> 4;



    temperature = temperature/0.0625;


    if(extendedMode)
    {


    }
    else
    {


    }


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x02);
    I2C_WriteByte(registerByte[0]);
    I2C_WriteByte(registerByte[1]);
    I2C_Stop();
}


void TMP112x_SetHighTempC(float temperature)
{
  uint8_t registerByte[2];
  _Bool extendedMode;


  if(temperature > 150.0f)
  {
    temperature = 150.0f;
  }
  if(temperature < -55.0)
  {
    temperature = -55.0f;
  }


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte[0] = I2C_ReadByte(1);
    registerByte[1] = I2C_ReadByte(0);
    I2C_Stop();

    extendedMode = (registerByte[1]&0x10)>>4;



    temperature = temperature/0.0625;


    if(extendedMode)
    {


    }
    else
    {


    }


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x03);
    I2C_WriteByte(registerByte[0]);
    I2C_WriteByte(registerByte[1]);
    I2C_Stop();
}


void TMP112x_SetLowTempF(float temperature)
{
  temperature = (temperature - 32)*5/9;
  TMP112x_SetLowTempC(temperature);
}


void TMP112x_SetHighTempF(float temperature)
{
  temperature = (temperature - 32)*5/9;
  TMP112x_SetHighTempC(temperature);
}


float TMP112x_ReadLowTempC(void)
{
  uint8_t registerByte[2];
  _Bool extendedMode;
  int16_t digitalTemp;
  float temperature;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte[0] = I2C_ReadByte(1);
    registerByte[1] = I2C_ReadByte(0);
    I2C_Stop();

    extendedMode = (registerByte[1]&0x10) >> 4;

    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x02);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte[0] = I2C_ReadByte(1);
    registerByte[1] = I2C_ReadByte(0);
    I2C_Stop();

  if(extendedMode)
  {

    digitalTemp = ((registerByte[0]) << 5) | (registerByte[1] >> 3);


    if(digitalTemp > 0xFFF)
 {
      digitalTemp |= 0xE000;
    }
  }
  else
  {

    digitalTemp = ((registerByte[0]) << 4) | (registerByte[1] >> 4);


    if(digitalTemp > 0x7FF)
 {
      digitalTemp |= 0xF000;
    }
  }

  return digitalTemp*0.0625;
}


float TMP112x_ReadHighTempC(void)
{
  uint8_t registerByte[2];
  _Bool extendedMode;
  int16_t digitalTemp;
  float temperature;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte[0] = I2C_ReadByte(1);
    registerByte[1] = I2C_ReadByte(0);
    I2C_Stop();

    extendedMode = (registerByte[1]&0x10) >> 4;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x03);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte[0] = I2C_ReadByte(1);
    registerByte[1] = I2C_ReadByte(0);
    I2C_Stop();

  if(extendedMode)
  {

    digitalTemp = ((registerByte[0]) << 5) | (registerByte[1] >> 3);


    if(digitalTemp > 0xFFF)
 {
      digitalTemp |= 0xE000;
    }
  }
  else
  {

    digitalTemp = ((registerByte[0]) << 4) | (registerByte[1] >> 4);


    if(digitalTemp > 0x7FF)
 {
      digitalTemp |= 0xF000;
    }
  }


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
    uint8_t registerByte;

    faultSetting = faultSetting&3;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte = I2C_ReadByte(0);
    I2C_Stop();


    registerByte &= 0xE7;
    registerByte |= faultSetting << 3;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_WriteByte(registerByte);
    I2C_Stop();
}


void TMP112x_SetAlertMode(_Bool mode)
{
  uint8_t registerByte;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_RepeatedStart();
    I2C_WriteByte(0x90 + 1);
    registerByte = I2C_ReadByte(0);
    I2C_Stop();


    registerByte &= 0xFD;
    registerByte |= mode << 1;


    I2C_Start();
    I2C_WriteByte(0x90);
    I2C_WriteByte(0x01);
    I2C_WriteByte(registerByte);
    I2C_Stop();
}
