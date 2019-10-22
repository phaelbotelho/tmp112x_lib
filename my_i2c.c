/* 
 * File:   my_i2c.c
 * Author: Raphael
 *
 * Created on 17 de Novembro de 2017, 09:56
 */

#include <xc.h>
#include "my_i2c.h"

void I2C_Init(unsigned char clock_output)
{
    SSPSTAT &= 0x3F; // Power on state
    SSPCON1 = 0x00; // Power on state
    SSPCON2 = 0x00; // Power on state
    SSPCON1 |= 0b00001000; // Select serial mode
    SSPSTAT |= 0b10000000; // Slew rate on/off
    
    I2C1_SCL = 1; // Set SCL1 (PORTC,3) pin to input
    I2C1_SDA = 1; // Set SDA1 (PORTC,4) pin to input
    
    SSPCON1 |= 0b00100000; // Enable synchronous serial port

    SSPADD = clock_output; // Clock = FOSC/(4 * (SSPADD + 1))
}

void I2C_Start(void)
{
    I2C_Idle();
    
    SSPCON2bits.SEN = 1;
    
    while(SSPCON2bits.SEN);
}

void I2C_RepeatedStart(void)
{
    I2C_Idle();
    
    SSPCON2bits.RSEN = 1;
    
    while(SSPCON2bits.RSEN);
}

void I2C_Stop(void)
{
    I2C_Idle();
    SSPCON2bits.PEN = 1;
    while(SSPCON2bits.PEN);
}

void I2C_Idle(void)
{
    while((SSPCON2 & 0x1F) | (SSPSTATbits.R_nW))
        continue;
}

void I2C_Close(void)
{
    SSPCON1 &= 0xDF;
}

unsigned char I2C_ReadByte(unsigned char acknowledge)
{
    unsigned char buffer_I2C = 0;
    
    I2C_Idle();
    
    if(((SSPCON1 & 0x0F) == 0x08) || ((SSPCON1 & 0x0F) == 0x0B)) //Master mode only
    {
        SSPCON2bits.RCEN = 1; // Enable master for 1 byte reception
    }
    
    while(!SSPSTATbits.BF); // Wait until byte received
    
    buffer_I2C = SSPBUF; // Read byte

    I2C_Idle();
    
    if(acknowledge == 1)
    {
        SSPCON2bits.ACKDT = 0;
        SSPCON2bits.ACKEN = 1;
        
        while(SSPCON2bits.ACKEN);
    }
    else
    {
        SSPCON2bits.ACKDT = 1;
        SSPCON2bits.ACKEN = 1;
        
        while(SSPCON2bits.ACKEN);
    }
    
    return (buffer_I2C); // Return with read byte
}

unsigned char I2C_WriteByte(unsigned char data_out)
{
    I2C_Idle();
    
    SSPBUF = data_out; // Write single byte to SSP1BUF
    
    if(SSPCON1bits.WCOL) // Test if write collision occurred
    {
        return (1); // If WCOL bit is set return negative #
    }
    else
    {
        if(((SSPCON1 & 0x0F) == 0x08) || ((SSPCON1 & 0x0F) == 0x0B)) //master mode only
        {
            while(SSPSTATbits.BF); // Wait until write cycle is complete
            
            I2C_Idle(); // Ensure module is idle
            
            if(SSPCON2bits.ACKSTAT) // Test for ACK condition received
            {
                return (2); // Return NACK
            }
            else
            {
                return (0); // Return ACK
            }
        }
    }
    
    return (0);
}