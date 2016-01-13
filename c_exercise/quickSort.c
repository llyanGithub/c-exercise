#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void quickSort(unsigned int* pArray, unsigned int len)
{
    int j = 0;
    int i;
    unsigned int temp;

    if (len == 0 || len == 1 || pArray == NULL) {
        return; 
    }

    for (i = 1; i < len; i++) {
        if (pArray[i] < pArray[0]) {
            temp = pArray[i];
            pArray[i] = pArray[j + 1];
            pArray[j + 1] = temp;
            j++;
        } 
    }

    temp = pArray[0];
    pArray[0] = pArray[j];
    pArray[j] = temp;
    
    quickSort(pArray, j);
    quickSort(pArray + j + 1, len - j - 1);
} 

void printArray(unsigned int* pArray, unsigned int len)
{
    int i;
    for (i = 0; i < len; i++) {
        printf("%d ", pArray[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    int i;
    unsigned int buf[50];
    srand(time(0));
    for (i = 0; i < sizeof(buf) / 4; i++) {
        buf[i] = rand() % 1000;
    }

    printArray(buf, sizeof(buf) / 4);
    printf("\n\n");
    quickSort(buf, sizeof(buf) / 4);
    printArray(buf, sizeof(buf) / 4);
}
