/*
 * flash.h
 *
 *  Created on: 2018Äê1ÔÂ16ÈÕ
 *      Author: lh
 */

#ifndef FLASH_H_
#define FLASH_H_

#include "global.h"

void initFlash();

void flashEraseSingleSegments(unsigned char * addr);

void flashWriteByte(unsigned char * addr, unsigned char data);

#endif /* FLASH_H_ */
