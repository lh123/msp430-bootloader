/*
 * bootloader.h
 *
 *  Created on: 2018Äê1ÔÂ16ÈÕ
 *      Author: lh
 */

#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

#include "global.h"

#define START_STATE 0
#define MENU_STATE 1
#define CLEAR_STATE 2
#define DOWNLOAD_STATE 3
#define START_APPLICATION_STATE 4
#define END_STATE 5

#define START_FLAG '1'
#define SUCCESS_FLAG '2'
#define FINISH_FLAG '3'

void initSystemClock();
void initTimer();
void disableTimer();

char checkApplication();

void eraseApplication();
void downloadProgram();
void reboot();

#endif /* BOOTLOADER_H_ */
