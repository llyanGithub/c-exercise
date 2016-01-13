#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

char* s = "I am lost please help me ----------------------------------";

uint8_t* Ramdom(uint8_t seed, uint8_t x1, uint8_t x2, uint32_t count)
{
    uint32_t bytes = count / 8;
    uint8_t* ramdom = malloc(bytes);
    int i = 0;
    int j = 0;
    uint8_t temp = 0;
    uint8_t input = 0;
    memset(ramdom, 0, bytes);
    for (; i < bytes; i++) {
        for(j = 0; j < 8; j++) {
            temp |= (seed & 0x01) << j;
//            printf("%c", (char)((seed & 0x01) + '0'));
            input = ((seed << x1) ^ (seed << x2)) & 0x80;
            seed = ((seed >> 1) & 0x7F) | input;
        } 
        ramdom[i] = temp;
        temp = 0;
    }

//    printf("\n");
    return ramdom;
}

uint8_t* encrypt(char* input, uint8_t* key)
{
   uint32_t bytes = strlen(input);
   uint8_t* output = malloc(bytes);
   memset(output, 0, bytes);

   int i;
   for (i = 0; i < bytes; i++) {
        output[i] = input[i] ^ key[i];
   }
   return output;
}

uint8_t* deencrypt(uint8_t* input, uint8_t* key, uint32_t bytes)
{
    uint8_t* output = malloc(bytes);
    memset(output, 0, bytes);

    int i;
    for (i = 0; i < bytes; i++) {
        output[i] = input[i] ^ key[i];
    }

    return output;
}

void printBinary(uint8_t* input, uint32_t bytes)
{
    int i;
    int j;
    for (i = 0; i < bytes; i++) {
        for (j = 0; j < 8; j++) {
            printf("%c", (char)(((input[i] >> j) & 0x01) + '0'));
        } 
    }
    printf("\n\n");
}

void monobitTest(uint8_t* key, uint32_t bytes)
{
    int i;
    int j;
    uint32_t count_0 = 0;
    uint32_t count_1 = 0;
    for (i = 0; i < bytes; i++) {
        for (j = 0; j < 8; j++) {
            uint8_t temp;
            temp = (key[i] >> j) & 0x01;
            if (temp == 0) {
                count_0++; 
            } else if (temp == 1) {
                count_1++; 
            }
        } 
    }
    printf("0 count : %d\n", count_0);
    printf("1 count : %d\n", count_1);
}
void pokerTest(uint8_t* key, uint32_t bytes)
{
    uint32_t count = bytes * 8;
    uint8_t* buf = malloc(count + 1);
    uint32_t array[6];
    int i;
    int j;
    int s = 0;
    int e = 0;
    uint32_t times = 0;
    memset(buf, 0, count + 1);
    memset(array, 0, sizeof(array));

    for (i = 0; i < bytes; i++){
        for(j = 0; j < 8; j++) {
            buf[i * 8 + j] = ((key[i] >> j) & 0x01) + '0';
        }
    }
    printf("%s\n", buf);

    while (1) {
        if (e == count) {
            break; 
        }
        if (buf[s] == buf[e]) {
            times++; 
            e++;
        } else {
            if (times >= 6) {
                array[5]++; 
            } else {
                array[times - 1]++; 
            } 
            s = e;
            times = 0;
        }
    } 

    if (times >= 6) {
        array[5]++; 
    } else {
        array[times - 1]++; 
    } 
    
    for (i = 0; i < 6; i++) {
        printf("%d : %d\n", i + 1, array[i]);
    }

}
void testRamdom(void)
{
    uint8_t* key = Ramdom(0x34, 2, 6, 32);
    monobitTest(key, 32 / 8);
    pokerTest(key, 32 / 8);
}

int main(void)
{
    uint8_t* key = Ramdom(0xaa, 2, 5, strlen(s) * 8);
    printBinary(key, strlen(s));
    uint8_t* en = encrypt(s, key);
    printBinary(en, strlen(s));
    uint8_t* de = deencrypt(en, key, strlen(s));
    int i;
    for (i = 0; i < strlen(s); i++) {
        printf("%c", de[i]);
    }
    printf("\n");
    testRamdom();

    return 0;
}
