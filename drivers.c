/* I2C Communication on MSP4320*/
#include "blink.h"


void I2C_Innit(){
    //  set the UCSWRST (setting the reset bit in UCBxCTL1)
    UCB0CTL1 |= UCSWRST;

    // innitalise all USCI registers in master mode
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC; // I2C Master, synchronous mode
    UCB0CTL1 = UCSSEL_2 + UCSWRST;        // Use SMCLK, keep SW reset

    // Set clock
    UCB0BR0 = 12;                         // fSCL = SMCLK/12 = ~100kHz
    UCB0BR1 = 0;

    // Set up I2C pins (P1.6 = SCL, P1.7 = SDA)
    P1SEL |= BIT6 + BIT7;    // Assign I2C pins to USCI_B0
    P1SEL2 |= BIT6 + BIT7;

    // Clear SW reset, resume operation
    UCB0CTL1 &= ~UCSWRST;

    // Enable I2C interrupts (optional)
    IE2 |= UCB0TXIE + UCB0RXIE;

}

void set_I2C_address(unsigned char address){
    UCB0I2CSA = address;  // Set the slave address
}

void I2C_Write_Data(unsigned char data){
    // Ensure the stop condition got sent before starting another TX
    while (UCB0CTL1 & UCTXSTP);

    // I2C TX, start condition
    UCB0CTL1 |= UCTR + UCTXSTT;

    // Wait for the start condition to be sent
    while ((IFG2 & UCB0TXIFG) == 0);

    // Send the data
    UCB0TXBUF = data;

    // Wait for the data to be transmitted
    while ((IFG2 & UCB0TXIFG) == 0);

    // Send stop condition
    UCB0CTL1 |= UCTXSTP;

    // Wait for the stop condition to be sent
    while (UCB0CTL1 & UCTXSTP);
}
