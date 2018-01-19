/*
 * utils.c
 *
 *  Created on: 2018年1月17日
 *      Author: lh
 */
#include "utils.h"

/**
 * @brief 将单个ASCII转换为对应的BIN
 * @param ascii ASCII码，EG：'A'
 * @return BIN，eg：'10'
 */
uchar asciiToHex(char ascii){
    if(ascii <= '9' && ascii >= '0'){
        return ascii - '0';
    }else if(ascii >= 'a' && ascii <= 'f'){
        return ascii - 'a' + 10;
    }else if(ascii >= 'A' && ascii <= 'F'){
        return ascii - 'A' + 10;
    }else{
        return 0xFF;
    }
}

/**
 * @brief 将两位的HEX转换为BIN
 * @param hex 两位的HEX(ASCII). eg: 0x2F
 * @return BIN
 */
uint hexToBin(const char *hex){
    uint temp;
    temp = asciiToHex(hex[0]) << 4;
    temp |= asciiToHex(hex[1]);
    return temp;
}

//:10 2462 00 464C5549442050524F46494C4500464C 33
uchar hexStringToBin(const char *str,HexFormat *hex){
    uint offset;
    uint index;
    uchar checkSum;
    uint temp;
    //start
    if(str[0] != ':'){
        return FAIL;
    }
    offset = 0;
    checkSum = 0;
    //length
    offset ++;
    hex->length = hexToBin(str + offset);
    checkSum += hex->length;
    if(hex->length > 16){
        return FAIL;
    }
    //address
    hex->address = 0;
    for(index = 0;index < 2;index ++){
        offset += 2;
        temp = hexToBin(str + offset);
        checkSum += temp;
        hex->address |= temp << 8 * (1 - index);
    }
    //type
    offset += 2;
    hex->type = hexToBin(str + offset);
    checkSum += hex->type;
    //data
    for(index = 0;index < hex->length ;index ++){
        offset += 2;
        temp = hexToBin(str + offset);
        hex->data[index] = temp;
        checkSum += temp;
    }
    //checksum
    offset += 2;
    temp = hexToBin(str + offset);
    if(temp == 0x100 - checkSum){
        return SUCCESS;
    }else{
        return FAIL;
    }
}
