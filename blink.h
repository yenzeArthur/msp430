#ifndef BLINK_H
    #define BLINK_H

    #define __MSP430G2553__
    #define CYCLES 1000000L

    #include <msp430.h>

    void I2C_Innit();
    void set_I2C_address(unsigned char address);
    void I2C_Write_Data(unsigned char data);

#endif