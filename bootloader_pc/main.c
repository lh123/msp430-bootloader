#include <stdio.h>
#include <string.h>
#include "serial.h"

typedef unsigned int uint;
typedef unsigned char uchar;

int main() {
    char buffer[10] = {0};
    printf("Please Enter Serial COM Port\n");
    gets(buffer);
    if(openSerial(buffer) == OPEN_FAIL) {
        printf("Open Serial Port Fail!\n");
        return 0;
    }
    char fileName[100];
    char fileBuff[50];
    printf("Please Enter Hex File Path:\n");
    scanf("%s",fileName);
    getchar();
    FILE *file = fopen(fileName,"r");
    if(file == 0) {
        printf("File Open Error!\n");
        return 0;
    }
    char flag;
    while(!feof(file)) {
        memset(fileBuff,0,sizeof(fileBuff));
        fgets(fileBuff,sizeof(fileBuff),file);
        uint length = strlen(fileBuff);
        if(length > 0 && fileBuff[length - 1] == '\n') {
            length -= 1;
        }
        if(length > 0) {
            printf(fileBuff);
            serialSendChar('s');
            serialSendChar((char)length);
            serialSendStr(fileBuff,length);
            serialReadChar(&flag);
            if(flag == 'n') {
                printf("Receive OK\n");
            } else {
                printf("Unknown Error!\n Flash Failed!\n");
                break;
            }
        }
    }
    serialSendChar('f');
    Sleep(1000);
    printf("Reboot MSP430\n");
    serialSendStr("r\r",2);
    serialReadChar(&flag);
    if(flag == 'n'){
        printf("Reboot Success!\n");
    }
    closeSerial();
    getchar();
    return 0;
}
