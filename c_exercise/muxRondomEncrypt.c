#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

uint8_t LFSR_1 = 0x12;
uint8_t LFSR_2 = 0x34;
uint8_t LFSR_3 = 0x56;
uint8_t LFSR_4 = 0x78;
uint8_t LFSR_5 = 0x9a;

uint8_t lfsr(uint8_t* pLfsr,uint8_t bytes, uint8_t x1, uint8_t x2)
{
   uint8_t ret = pLfsr[bytes - 1] & 0x01; 
   uint8_t input = (pLfsr[x1 / 8] << ((x1 - 1) % 8)) & (pLfsr[x2 / 8] << ((x2 - 1) % 8));
   int i;
   for (i = bytes - 1; i >= 0; i--) {
        uint8_t temp = 0;
        if (i != 0) {
            temp = (pLfsr[i - 1] & 0x01) << 7;
            pLfsr[i] = ((pLfsr[i] >> 1) & 0x7F) | temp;
        } else {
            pLfsr[i] = (pLfsr[i] >> 1) & 0x7F;
        }
   }
   pLfsr[0] = pLfsr[0] | input; 

   return ret;
}

void encrypt(void)
{
   uint8_t addr = lfsr(&LFSR_1, 1, 2, 6) | (lfsr(&LFSR_1, 1, 2, 6) << 1);
   uint8_t output_1 = lfsr(&LFSR_2, 1, 2, 6);
   uint8_t output_2 = lfsr(&LFSR_3, 1, 2, 6);
   uint8_t output_3 = lfsr(&LFSR_4, 1, 2, 6);
   uint8_t output_4 = lfsr(&LFSR_5, 1, 2, 6);
   printf("addr = %u\n", addr);
   printf("output_1 = %u\n", output_1);
   printf("output_2 = %u\n", output_2);
   printf("output_3 = %u\n", output_3);
   printf("output_4 = %u\n", output_4);

   switch (addr) {
        case 0x0:
            printf("%c", output_1 + '0');
            break;
        case 0x1:
            printf("%c", output_2 + '0');
            break;
        case 0x2:
            printf("%c", output_3 + '0');
            break;
        case 0x3:
            printf("%c", output_4 + '0');
            break;
        default:
            break;
   }
   printf("\n");
}

int main(void)
{
    int i;
    for (i = 0; i < 8; i++){
        encrypt();
    }
    printf("\n");
    return 0;
}
