/* 
 * File:   tmp122x.h
 * Author: Raphael
 *
 * Created on October 22, 2019, 11:06 AM
 */

#ifndef TMP122X_H
#define	TMP122X_H

#include <stdint.h>
#include <stdbool.h>

#define TMP112x_ADR 0x90 // A0 connected to GND.
//#define TMP112x_ADR 0x92 // A0 connected to VCC.
//#define TMP112x_ADR 0x94 // A0 connected to SDA.
//#define TMP112x_ADR 0x96 // A0 connected to SCL.

#define TEMPERATURE_REGISTER 0x00
#define CONFIG_REGISTER      0x01
#define T_LOW_REGISTER       0x02
#define T_HIGH_REGISTER      0x03

void TMP112x_Init();

float TMP112x_ReadTemp();

// Set the conversion rate (0-3)
// 0 - 0.25 Hz
// 1 - 1 Hz
// 2 - 4 Hz (default)
// 3 - 8 Hz
void TMP112x_SetConversionRate(uint8_t rate);

// Enable or disable extended mode
// 0 - disabled (-55C to +128C)
// 1 - enabled  (-55C to +150C)
void TMP112x_SetExtendedMode(bool mode);

// Set the polarity of Alert
// 0 - Active LOW
// 1 - Active HIGH
void TMP112x_SetAlertPolarity(bool polarity);

// Set the number of consecutive faults
// 0 - 1 fault
// 1 - 2 faults
// 2 - 4 faults
// 3 - 6 faults
void TMP112x_SetFault(uint8_t faultSetting);

// Set Alert type
// 0 - Comparator Mode: Active from temp > T_HIGH until temp < T_LOW
// 1 - Thermostat Mode: Active when temp > T_HIGH until any read operation occurs
void TMP112x_SetAlertMode(bool mode);


#endif	/* TMP122X_H */

