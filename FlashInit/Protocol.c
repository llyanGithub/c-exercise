#include "Protocol.h"

struct boot_pk
{
    uint8_t cmdId;
    union {
        struct {
            uint8_t reserved:4;
            uint8_t dir:2;
            uint8_t fSeq:1;
            uint8_t fAck:1;
        }bf;
        uint8_t byteVal;
    } opt;
    uint8_t nArg;
    uint32_t pswd;
    uint32_t arg[1];
};

void sendPkt()
{

}

void readPkt()
{

}

void jtag_switch()
{

}

void read_ram()
{

}

void write_ram()
{

}

void read_flash()
{

}

void bootAt()
{

}

void reboot()
{

}
