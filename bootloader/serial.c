/*
 * serial.c
 *
 *  Created on: 2018Äê1ÔÂ16ÈÕ
 *      Author: lh
 */

#include "serial.h"

void initUART() {
    P1SEL = 0x06;
    P1SEL2 = 0x06;

    UCA0CTL0 = 0x00;
    UCA0CTL1 = 0x01 << 7 | 0x01;
    UCA0BR0 = 104;
    UCA0BR1 = 0x00;
    UCA0MCTL = 0x01 << 1;
    UCA0CTL1 &= ~0x01;
}

void uartSendChar(char ch) {
    UCA0TXBUF = ch;
    while (!UCA0TXIFG);
    IFG2 &= ~0x02;
}

void uartSendString(char *str) {
    while (*str != '\0') {
        uartSendChar(*str);
        str++;
    }
}

void uartReadChar(char *ch) {
    while (!UCA0RXIFG);
    *ch = UCA0RXBUF;
    IFG2 &= ~0x01;
}

void uartReadString(char *str, unsigned int length) {
    unsigned int index;
    char temp;
    index = 0;
    temp = 0;
    while (1) {
        uartReadChar(&temp);
        uartSendChar(temp);
        if (temp == '\r') {
            uartSendChar('\n');
            break;
        }
        if (index < length) {
            str[index] = temp;
            index++;
        }
    }
    str[index] = '\0';
}
