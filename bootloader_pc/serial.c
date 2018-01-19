#include "serial.h"
#include <windows.h>

HANDLE handle;

unsigned char openSerial(const char * name) {
    handle = CreateFile(TEXT(name),GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if(handle == INVALID_HANDLE_VALUE) {
        return OPEN_FAIL;
    }
    SetupComm(handle,1024,1024);
    COMMTIMEOUTS timeOuts;
    memset(&timeOuts, 0, sizeof(timeOuts));
    SetCommTimeouts(handle, &timeOuts);

    DCB dcb;
    memset(&dcb, 0, sizeof(dcb));
    dcb.BaudRate = BAUD_9600;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.StopBits = ONE5STOPBITS;
    SetCommState(handle, &dcb);
    PurgeComm(handle, PURGE_RXCLEAR | PURGE_TXCLEAR);
    return OPEN_SUCCESS;
}

void closeSerial() {
    CloseHandle(handle);
}

void serialSendChar(char ch) {
    DWORD sendCount = 0;
    while(sendCount < 1) {
        WriteFile(handle,&ch,1,&sendCount,NULL);
    }
}

void serialSendStr(char *str,unsigned int length) {
    DWORD sendTotalCount = 0;
    DWORD sendCount = 0;
    while(sendTotalCount < length) {
        WriteFile(handle, str + sendTotalCount,length - sendTotalCount,&sendCount,NULL);
        sendTotalCount += sendCount;
        sendCount = 0;
    }
}
void serialReadChar(char *ch) {
    char temp[1] = {0};
    DWORD readCount = 0;
    while(readCount < 1) {
        ReadFile(handle,temp,1,&readCount,NULL);
    }
    *ch = temp[0];
}

