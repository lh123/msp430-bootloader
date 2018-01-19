#include "bootloader.h"
#include "serial.h"
#include "flash.h"
#include "utils.h"

char *menuStr = "------------MSP430 BOOT MENU------------\r\n"
        " (D):Download Program From Serial\r\n"
        " (E):Erase Flash\r\n"
        " (R):Reboot\r\n";

char *commandStr = "command:";
char *commandErrorStr = "command error!\r\n";

typedef int (*ApplicationMainFunc)();

const ApplicationMainFunc * const appMainFunc =
        (const ApplicationMainFunc * const ) 0xCA1E;

uint __attribute__((section(".mode_flag"))) isBootMode;

unsigned char currentState;
unsigned int count;
uint preCount;

void bootloader_main() {
    char command[5] = { 0 };
    isBootMode = 1;
    initSystemClock();
    initTimer();
    initUART();
    initFlash();
    _EINT();
    currentState = START_STATE;
    count = 0;
    preCount = count;
    uartSendString("Press Any Key to Interrupt Boot!\r\n");
    while (1) {
        switch (currentState) {
            case START_STATE:
                if (count - preCount < 6 && UCA0RXIFG) {
                    uartReadChar((char *) 0x00);
                    currentState = MENU_STATE;
                    uartSendString(menuStr);
                    uartSendString(commandStr);
                    disableTimer();
                    _DINT();
                } else if (count - preCount > 6) {
                    currentState = START_APPLICATION_STATE;
                    disableTimer();
                    _DINT();
                }
                break;
            case MENU_STATE:
                uartReadString(command, 5);
                if (command[1] != '\0') {
                    uartSendString(commandErrorStr);
                    uartSendString(commandStr);
                } else {
                    switch (command[0]) {
                        case 'D':
                        case 'd':
                            downloadProgram();
                            uartSendString(commandStr);
                            break;
                        case 'E':
                        case 'e':
                            eraseApplication();
                            uartSendString(commandStr);
                            break;
                        case 'R':
                        case 'r':
                            __delay_cycles(500000);
                            reboot();
                            break;
                        default:
                            uartSendString(commandErrorStr);
                            uartSendString(commandStr);
                            break;
                    }
                }
                break;
            case START_APPLICATION_STATE:
                if (checkApplication() == 1) {
                    currentState = END_STATE;
                    isBootMode = 0;
                    (*appMainFunc)();
                } else {
                    currentState = MENU_STATE;
                    uartSendString("Boot Error, No Application Found!\r\n");
                    uartSendString(menuStr);
                    uartSendString(commandStr);
                }
                break;
        }
    }
}

void initSystemClock() {
    DCOCTL = CALDCO_1MHZ;
    BCSCTL1 = CALBC1_1MHZ;
}

void initTimer() {
    TA0CTL |= 0x01 << 2;
    TA0CTL = (0x02 << 8) + (0x03 << 6) + (0x01 << 4); //125000
    TA0CCTL0 |= 0x01 << 4;
    TA0CCR0 = 62500; //0.5s
}

void disableTimer() {
    TA0CTL |= 0x01 << 2;
    TA0CTL &= ~(0x03 << 4);
    TA0CCTL0 &= ~(0x01 << 4);
}

char checkApplication() {
    if ((uint) (*appMainFunc) == 0xFFFF) {
        return 0;
    } else {
        return 1;
    }
}
void eraseApplication() {
    unsigned char *ptr;
    _DINT();
    uartSendString("Erase Start\r\n");
    for (ptr = APP_SEGMENT_START; ptr <= APP_SEGMENT_END; ptr += 0x200) {
        flashEraseSingleSegments(ptr);
        uartSendChar('.');
    }
    uartSendString("\r\nErase Complete!\r\n");
}

void downloadProgram() {
    HexFormat format;
    uint index;
    uchar *ptr;
    char buffer[43];
    char command = 0;
    char length;
    char temp;
    uartSendChar('n');
    while (1) {
        uartReadChar(&command);
        switch (command) {
            case 's':
                uartReadChar(&length);
                for (index = 0; index < length; index++) {
                    uartReadChar(&temp);
                    buffer[index] = temp;
                }
                if (!hexStringToBin(buffer, &format)) {
                    uartSendChar('e');
                    return;
                }
                if (((uchar *) (format.address)) < APP_ROM_START
                        || ((uchar *) (format.address)) > APP_ROM_END) {
                    uartSendChar('e');
                    return;
                }
                if (format.type == 0) {
                    for (index = 0; index < format.length; index++) {
                        ptr = ((uchar *) (format.address)) + index;
                        flashWriteByte(ptr, format.data[index]);
                    }
                }
                uartSendChar('n');
                break;
            case 'f':
                uartSendChar('n');
                return;
        }
    }
}

void reboot() {
    WDTCTL = 0x00;
}
