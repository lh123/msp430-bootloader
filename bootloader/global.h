/*
 * global.h
 *
 *  Created on: 2018Äê1ÔÂ16ÈÕ
 *      Author: lh
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

typedef unsigned char uchar;
typedef unsigned int uint;

#define APP_ROM_START ((unsigned char *)(0xCA00))
#define APP_ROM_END ((unsigned char *)(0xFDFF))

#define APP_SEGMENT_START APP_ROM_START
#define APP_SEGMENT_END (APP_ROM_END - 512 + 1)


#define sfr_b(X) extern volatile unsigned char X
#define sfr_w(X) extern volatile unsigned int X

#define _EINT() asm("nop\r\neint")
#define _DINT() asm("nop\r\ndint")
#define __delay_cycles(X) __delay_cycles(X)

extern uint count;

sfr_w(WDTCTL);

sfr_b(P1SEL);
sfr_b(P1SEL2);

sfr_b(DCOCTL);
sfr_b(BCSCTL1);
sfr_b(CALDCO_1MHZ);
sfr_b(CALBC1_1MHZ);

sfr_w(TA0CTL);
sfr_w(TA0CCTL0);
sfr_w(TA0CCR0);
sfr_w(TAIV);

sfr_b(UCA0CTL0);
sfr_b(UCA0CTL1);
sfr_b(UCA0BR0);
sfr_b(UCA0BR1);
sfr_b(UCA0MCTL);
sfr_b(UCA0STAT);
sfr_b(UCA0STAT);
sfr_b(UCA0RXBUF);
sfr_b(UCA0TXBUF);

#define FRKEY   0xA500
sfr_w(FCTL1);
#define WRT     0x0040
#define ERASE   0x0002
sfr_w(FCTL2);
#define FSSEL_SMCLK 0x0080
#define FN_3        0x0002
sfr_w(FCTL3);
#define LOCK    0x0010
#define WAIT    (0x01 << 3)
#define BUSY    0x01

sfr_b(IE2);
sfr_b(IFG2);

#define TRAPINT_VECT        0
#define PORT1_VECT          1
#define PORT2_VECT          2
#define ADC10_VECT          3
#define USCIAB0TX_VECT      4
#define USCIAB0RX_VECT      5
#define TIMER0_A1_VECT      6
#define TIMER0_A0_VECT      7
#define WDT_VECT            8
#define COMPARATORA_VECT    9
#define TIMER1_A1_VECT      10
#define TIMER1_A0_VECT      11
#define NMI_VECT            12
#define RESET_VECT          13

extern uint __attribute__((section(".mode_flag"))) isBootMode;

#endif /* GLOBAL_H_ */
