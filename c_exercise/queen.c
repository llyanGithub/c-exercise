#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

uint8_t col[9];
uint8_t help_1[16];
uint8_t help_2[16];

uint16_t count = 0;

int help(uint8_t val_1, uint8_t val_2)
{
    uint8_t num_1, num_2;
    num_1 = val_1 + val_2 -1;
    num_2 = (8 - val_1 + 1) + val_2 -1;
    if (col[val_2] || help_1[num_1] || help_2[num_2]) {
        return -1; 
    } else {
        col[val_2] = 1; 
        help_1[num_1] = 1;
        help_2[num_2] = 1;
        return 0;
    }
}

void help2(uint8_t val_1, uint8_t val_2)
{
    uint8_t num_1, num_2;
    num_1 = val_1 + val_2 -1;
    num_2 = (8 - val_1 + 1) + val_2 -1;
    
    col[val_2] = 0; 
    help_1[num_1] = 0;
    help_2[num_2] = 0;
}

void queen_start(uint8_t num)
{
    int i;
    if (num > 8) {
        count++; 
        return;
    }
    for (i = 1; i < 9; i++) {
        if (0 == help(num, i)) {
            queen_start(num + 1);
        } else {
            continue; 
        }
        help2(num, i);
    }
}

int main(void)
{
    memset(col, 0, sizeof(col));
    memset(help_1, 0, sizeof(help_1));
    memset(help_2, 0, sizeof(help_2));

    queen_start(1);
    printf("count : %d\n", count);

    return 0;
}
