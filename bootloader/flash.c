#include "flash.h"

void initFlash() {
    FCTL2 = FRKEY + FSSEL_SMCLK + FN_3;
}

//Segment size is 512B
void flashEraseSingleSegments(unsigned char * addr) {
    unsigned char *ptr;
    ptr = addr;
    FCTL1 = FRKEY + ERASE;
    FCTL3 = FRKEY;

    *ptr = 0xFF;
    while (FCTL3 & BUSY);

    FCTL1 = FRKEY;
    FCTL3 = FRKEY + LOCK;
}

void flashWriteByte(unsigned char * addr, unsigned char data) {
    unsigned char *ptr;
    ptr = addr;
    FCTL1 = FRKEY + WRT;
    FCTL3 = FRKEY;

    *ptr = data;
    while (FCTL3 & BUSY);

    FCTL1 = FRKEY;
    FCTL3 = FRKEY + LOCK;
}
