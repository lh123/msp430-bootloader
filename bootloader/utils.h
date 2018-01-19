/*
 * utils.h
 *
 *  Created on: 2018Äê1ÔÂ16ÈÕ
 *      Author: lh
 */

#ifndef UTILS_H_
#define UTILS_H_

#define SUCCESS 1
#define FAIL 0

#include "global.h"

typedef struct HEX_Format{
    uint length;
    uint type;
    uint address;
    uchar data[16];
} HexFormat;

uchar asciiToHex(char ascii);
uint hexToBin(const char *hex);

uchar hexStringToBin(const char *str,HexFormat *bin);

#endif /* UTILS_H_ */
