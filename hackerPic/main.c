#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#include "common.h"

char* chars = "~!@#$%^&*()_+-=qwertyuiop[]\\{}|1234567890asdfghjkl;':zxcvbnm,./<>?";
//char* chars = "1234567890";
pthread_mutex_t mut;

void clearScreen()
{
    printf("\33[2J");   // clear screen
    printf("\33[?25l"); // hide cursor
}

int getScreenSize(uint16_t* width, uint16_t* height)
{
    int cols;
    int lines;
#ifdef TIOCGSIZE
    struct ttysize ts;
    ioctl(STDIN_FILENO, TIOCGSIZE, &ts);
    *width = ts.ts_cols;
    *height = ts.ts_lines;
#elif defined(TIOCGWINSZ)
    struct winsize ts;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ts);
    *width = ts.ws_col;
    *height = ts.ws_row;
#endif /* TIOCGSIZE */

    return 0;
}

void drawChar(uint16_t x, uint16_t y, char s)
{
    pthread_mutex_lock(&mut);
    printf("\33[%d;%dH", y, x);
    printf("%c", s);
    fflush(stdout);
    pthread_mutex_unlock(&mut);
}

uint16_t p = 1;
void* threadFunc(void* arg)
{
    uint16_t height = ((uint16_t*)arg)[0];
    uint16_t pos = ((uint16_t*)arg)[1];
    uint16_t strLen = strlen(chars);
    int i;

//    printf("%d X %d\n", height, pos);
//    drawChar(pos, 1, 'a'); 
    srand(time(0));
    while (1) {
        for (i = 1; i < height; i++) {
            drawChar(pos, i, chars[rand()%strLen]); 
        } 
//        printf("This is thread! %d X %d %c\n", width, height, chars[rand()%strLen]);
        usleep(1000);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    uint16_t size[2];
    uint16_t* width = &size[0];
    uint16_t* height = &size[1];
    int i;
    pthread_t ntid;

    clearScreen();
    getScreenSize(width, height);

//    printf("%d X %d\n", *width, *height);

    pthread_mutex_init(&mut,NULL); 
    for (i = 1; i < *width; i++) {
        if (i % 2 == 0) {
            uint16_t* arg = malloc(sizeof(uint16_t) * 2);
            arg[0] = *height;
            arg[1] = i;
            pthread_create(&ntid, NULL, threadFunc, arg);
        } 
    }
    while (1);
}
