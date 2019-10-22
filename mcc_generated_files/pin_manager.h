/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F18323
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB 	          :  MPLAB X 5.20	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SDA1 aliases
#define SDA1_TRIS                 TRISAbits.TRISA4
#define SDA1_LAT                  LATAbits.LATA4
#define SDA1_PORT                 PORTAbits.RA4
#define SDA1_WPU                  WPUAbits.WPUA4
#define SDA1_OD                   ODCONAbits.ODCA4
#define SDA1_ANS                  ANSELAbits.ANSA4
#define SDA1_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define SDA1_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define SDA1_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define SDA1_GetValue()           PORTAbits.RA4
#define SDA1_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define SDA1_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define SDA1_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define SDA1_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define SDA1_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define SDA1_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define SDA1_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define SDA1_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set SCL1 aliases
#define SCL1_TRIS                 TRISAbits.TRISA5
#define SCL1_LAT                  LATAbits.LATA5
#define SCL1_PORT                 PORTAbits.RA5
#define SCL1_WPU                  WPUAbits.WPUA5
#define SCL1_OD                   ODCONAbits.ODCA5
#define SCL1_ANS                  ANSELAbits.ANSA5
#define SCL1_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define SCL1_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define SCL1_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define SCL1_GetValue()           PORTAbits.RA5
#define SCL1_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define SCL1_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define SCL1_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define SCL1_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define SCL1_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define SCL1_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define SCL1_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define SCL1_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set LED2 aliases
#define LED2_TRIS                 TRISCbits.TRISC0
#define LED2_LAT                  LATCbits.LATC0
#define LED2_PORT                 PORTCbits.RC0
#define LED2_WPU                  WPUCbits.WPUC0
#define LED2_OD                   ODCONCbits.ODCC0
#define LED2_ANS                  ANSELCbits.ANSC0
#define LED2_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define LED2_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define LED2_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define LED2_GetValue()           PORTCbits.RC0
#define LED2_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define LED2_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define LED2_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define LED2_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define LED2_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define LED2_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define LED2_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set LED1 aliases
#define LED1_TRIS                 TRISCbits.TRISC1
#define LED1_LAT                  LATCbits.LATC1
#define LED1_PORT                 PORTCbits.RC1
#define LED1_WPU                  WPUCbits.WPUC1
#define LED1_OD                   ODCONCbits.ODCC1
#define LED1_ANS                  ANSELCbits.ANSC1
#define LED1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define LED1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define LED1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define LED1_GetValue()           PORTCbits.RC1
#define LED1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define LED1_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define LED1_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define LED1_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define LED1_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define LED1_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define LED1_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set RC3 procedures
#define RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RC3_GetValue()              PORTCbits.RC3
#define RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RC3_SetPullup()             do { WPUCbits.WPUC3 = 1; } while(0)
#define RC3_ResetPullup()           do { WPUCbits.WPUC3 = 0; } while(0)
#define RC3_SetAnalogMode()         do { ANSELCbits.ANSC3 = 1; } while(0)
#define RC3_SetDigitalMode()        do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set EN_485 aliases
#define EN_485_TRIS                 TRISCbits.TRISC4
#define EN_485_LAT                  LATCbits.LATC4
#define EN_485_PORT                 PORTCbits.RC4
#define EN_485_WPU                  WPUCbits.WPUC4
#define EN_485_OD                   ODCONCbits.ODCC4
#define EN_485_ANS                  ANSELCbits.ANSC4
#define EN_485_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define EN_485_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define EN_485_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define EN_485_GetValue()           PORTCbits.RC4
#define EN_485_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define EN_485_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define EN_485_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define EN_485_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define EN_485_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define EN_485_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define EN_485_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define EN_485_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/