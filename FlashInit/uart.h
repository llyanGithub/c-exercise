#ifndef _UART_H
#define _UART_H

int uart_init(int port, int baudrate, int databits,int stopbits,int parity);
int uart_read(unsigned char * recvBuf, int bufLen);
int uart_write(unsigned char * recvBuf, int bufLen);
int uart_open(void);
int uart_close(void);

#endif

