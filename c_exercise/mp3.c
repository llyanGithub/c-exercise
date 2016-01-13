#include <stdio.h>
#include <stdlib.h>

void help(int num)
{
    int cur = 1;
    int i;
    for (i = 0; i < num; i++) {
        printf("%d\n", cur); 
        if (cur * 10 <= num) {
            cur = cur* 10; 
            continue;
        } else if (cur + 1 <= num) {
            cur = cur + 1;
        } else if (cur / 10 + 1 <= num) {
            cur = cur / 10 + 1; 
        }
        while (cur % 10 == 0) {
            cur = cur / 10; 
        }
    }
}

int main(int argc, char** argv)
{
    int num = atoi(argv[1]);
    help(num);
    return 0;
}
