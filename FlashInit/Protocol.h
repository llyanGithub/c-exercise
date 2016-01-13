#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "common.h"
#include "uart.h"

void sendPkt();
void readPkt();
void jtag_switch();
void read_ram();
void write_ram();
void read_flash();
void bootAt();
void reboot();

#endif
