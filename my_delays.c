/* 
 * File:   my_delays.c
 * Author: |H_e_c_t_o_r|
 * 
 */

#include <xc.h>
#include "mcc_generated_files/device_config.h"
#include "my_delays.h"

void Delay_ms(unsigned int count)
{
    unsigned int i;
    
    for(i = 0; i < count; i ++)
    {
        __delay_ms(1);
    }
}

void Delay_us(unsigned int count)
{
    unsigned int i;
    
    for(i = 0; i < count; i ++)
    {
        __delay_us(1);
    }
}