#include "common.h"

#include <errno.h>   
#include <fcntl.h>
#include <fcntl.h>
#include <pthread.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>   
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include "uart.h"

#define FALSE 0
#define TRUE 1

static char uart_path[20];
static int uart_fd;

static int speed_arr[] = {B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300,
    B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300, };
static int name_arr[] = {115200, 38400, 19200, 9600, 4800, 2400, 1200,  300, 
    115200, 38400, 19200, 9600, 4800, 2400, 1200,  300, };


static void uart_linuxSetSpeed(int fd, int speed)
{
    int   i; 
    int   status; 
    struct termios   Opt;
    tcgetattr(fd, &Opt); 
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++) { 
        if  (speed == name_arr[i]) {     
            tcflush(fd, TCIOFLUSH);     
            cfsetispeed(&Opt, speed_arr[i]);  
            cfsetospeed(&Opt, speed_arr[i]);   
            status = tcsetattr(fd, TCSANOW, &Opt);  
            if  (status != 0) {        
                perror("tcsetattr fd1");  
                return;     
            }    
            tcflush(fd,TCIOFLUSH);   
        }  
    }
}

static void uart_linuxSetTermios(struct termios * pNewtio, int uBaudRate) 
{ 
    bzero(pNewtio, sizeof(struct termios)); /* clear struct for new port settings */ 
 
    //8N1 
    pNewtio->c_cflag = uBaudRate | CS8 | CREAD | CLOCAL; 
    pNewtio->c_iflag = IGNPAR; 
 
    pNewtio->c_oflag = 0; 
    pNewtio->c_lflag = 0; //non ICANON 
    /* 
     initialize all control characters 
     default values can be found in /usr/include/termios.h, and 
     are given in the comments, but we don't need them here 
     */ 
    pNewtio->c_cc[VINTR] = 0; /* Ctrl-c */ 
    pNewtio->c_cc[VQUIT] = 0; /* Ctrl-\ */ 
    pNewtio->c_cc[VERASE] = 0; /* del */ 
    pNewtio->c_cc[VKILL] = 0; /* @ */ 
    pNewtio->c_cc[VEOF] = 4; /* Ctrl-d */ 
    pNewtio->c_cc[VTIME] = 1; /* inter-character timer, timeout VTIME*0.1 */ 
    pNewtio->c_cc[VMIN] = 1; /* blocking read until VMIN character arrives */ 
//    pNewtio->c_cc[VSWTC] = 0; /* '\0' */ 
    pNewtio->c_cc[VSTART] = 0; /* Ctrl-q */ 
    pNewtio->c_cc[VSTOP] = 0; /* Ctrl-s */ 
    pNewtio->c_cc[VSUSP] = 0; /* Ctrl-z */ 
    pNewtio->c_cc[VEOL] = 0; /* '\0' */ 
    pNewtio->c_cc[VREPRINT] = 0; /* Ctrl-r */ 
    pNewtio->c_cc[VDISCARD] = 0; /* Ctrl-u */ 
    pNewtio->c_cc[VWERASE] = 0; /* Ctrl-w */ 
    pNewtio->c_cc[VLNEXT] = 0; /* Ctrl-v */ 
    pNewtio->c_cc[VEOL2] = 0; /* '\0' */ 
}


static int uart_linuxSetBasic(int fd,int databits,int stopbits,int parity)
{ 
    struct termios options; 
    if  ( tcgetattr( fd,&options)  !=  0) { 
        perror("SetupSerial 1");     
        return(FALSE);  
    }
    options.c_cflag &= ~CSIZE; 
    switch (databits)
    {   
        case 7:     
        options.c_cflag |= CS7; 
        break;
        case 8:     
        options.c_cflag |= CS8;
        break;   
        default:    
        fprintf(stderr,"Unsupported data size\n"); return (FALSE);  
    }
    switch (parity) 
    {   
        case 'n':
        case 'N':    
        options.c_cflag &= ~PARENB;   /* Clear parity enable */
        options.c_iflag &= ~INPCK;     /* Enable parity checking */ 
        break;  
        case 'o':   
        case 'O':     
        options.c_cflag |= (PARODD | PARENB);
        options.c_iflag |= INPCK;             /* Disnable parity checking */ 
        break;  
        case 'e':  
        case 'E':   
        options.c_cflag |= PARENB;     /* Enable parity */    
        options.c_cflag &= ~PARODD;
        options.c_iflag |= INPCK;       /* Disnable parity checking */
        break;
        case 'S': 
        case 's':  /*as no parity*/   
        options.c_cflag &= ~PARENB;
        options.c_cflag &= ~CSTOPB;break;  
        default:   
        fprintf(stderr,"Unsupported parity\n");    
        return (FALSE);  
    }  
    switch (stopbits)
    {   
        case 1:    
        options.c_cflag &= ~CSTOPB;  
        break;  
        case 2:    
        options.c_cflag |= CSTOPB;  
        break;
        default:    
        fprintf(stderr,"Unsupported stop bits\n");  
        return (FALSE); 
    } 
    options.c_cflag &= ~CRTSCTS;
    /* Set input parity option */ 
    if (parity != 'n')   
        options.c_iflag |= INPCK; 
    tcflush(fd,TCIFLUSH);
    options.c_cc[VTIME] = 150;
    options.c_cc[VMIN] = 0; /* Update the options and do it NOW */
    options.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
    options.c_oflag  &= ~OPOST;   /*Output*/
    if (tcsetattr(fd,TCSANOW,&options) != 0)   
    { 
        perror("SetupSerial 3");   
        return (FALSE);  
    } 
    return (TRUE);  
}

static int uart_linuxOpenDevice(char* path){
    struct termios oldtio, newtio;
    int fd = open(path, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd < 0) {
        fprintf(stderr,"open %s failed\n", path);
        return fd;
    }
    printf("Open...\n");
    
#if 0    
    uart_set_speed(fd,19200);
    if (uart_set_parity(fd,8,1,'N') == FALSE)  {
        printf("Set Parity Error\n");
        exit (0);
    }

#endif

    tcgetattr(fd, &oldtio); /* save current serial port settings */ 
#if 1
//	setTermios(&newtio, B115200); 
    printf("BANDRate: 115200\r\n");
#else
    setTermios(&newtio, B19200); 
    printf("BANDRate: 19200\r\n"):

#endif

	tcflush(fd, TCIFLUSH); 
	tcsetattr(fd, TCSANOW, &newtio); 	
    tcflush(fd, TCIFLUSH); 
    
    return fd;
}

int uart_open(void)
{
    return uart_linuxOpenDevice(uart_path);
}


int uart_close(void){
    close(uart_fd);
    uart_fd = 0 ;
    return 0;
}

int uart_read(unsigned char * recvBuf, int bufLen)
{
    int thisRead;
    int offset = 0;
	
    do {
        thisRead = read(uart_fd, &recvBuf[offset], bufLen);
        if (thisRead < 0) {
            //perror("error!");
            return -1;
        }
        offset += thisRead;
        } while(offset < bufLen);

	return offset;
}


int uart_init(int port, int baudrate, int databits,int stopbits,int parity)
{
    sprintf(uart_path, "/dev/ttyS%d", port - 1);
	uart_fd = uart_linuxOpenDevice(uart_path);
	
	uart_linuxSetSpeed(uart_fd, baudrate);
	uart_linuxSetBasic(uart_fd, databits, stopbits, 's');
	
	return uart_fd;
}


int uart_write(unsigned char * recvBuf, int bufLen){
    //write(uart_fd, &bufLen, 1);
    write(uart_fd, recvBuf, bufLen);
    tcflush(uart_fd,TCIOFLUSH);    
    return 0;
}

