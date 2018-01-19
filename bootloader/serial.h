/*
 * serial.h
 *
 *  Created on: 2018Äê1ÔÂ16ÈÕ
 *      Author: lh
 */

#ifndef SERIAL_H_
#define SERIAL_H_
#include "global.h"

//#define BUSY (UCA0STAT & 0x01)

#define UCA0TXIFG ((IFG2 & (0x01 << 1)) >> 1)
#define UCA0RXIFG (IFG2 & 0x01)

void initUART();
void uartSendChar(char ch);
void uartReadChar(char *ch);
void uartSendString(char *str);
void uartReadString(char *str,unsigned int num);

#endif /* SERIAL_H_ */
