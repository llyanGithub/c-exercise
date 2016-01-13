#include "common.h"
#include "tree.h"
#include "draw.h"

struct width_s {
    uint16_t width;
    struct width_s* next;
};
typedef struct width_s width_t;

int itoa(uint32_t num, uint8_t* buf, uint8_t radix)
{
    uint8_t tBuf[10];
    uint32_t tmp = num;
    uint16_t cnt = 0;
    int i;

    if (radix <= 10) {
        while (tmp != 0) {
            tBuf[cnt++] = tmp % radix + '0';
            tmp = tmp / radix;
        }
    }

    for (i = 0; i < cnt; i++) {
        buf[i] = tBuf[cnt - 1 - i]; 
    }
    buf[i] = 0;

//    printf("%s\n", buf);
    return 0;
}

binTree_t* genTree(uint32_t* pArray, uint32_t len)
{
    binTree_t* pRoot;
    binTree_t* pLeft;
    binTree_t* pRight;
    uint32_t pRootIndex;

    if (len == 0) {
        return NULL; 
    }

    srand(time(0));
    pRootIndex = rand() % len;
//    printf("random = %d\n", pRootIndex);
    pRoot = (binTree_t*)malloc(sizeof(binTree_t));
    pRoot->value = pArray[pRootIndex];
    pRoot->left = genTree(pArray, pRootIndex);
    pRoot->right = genTree(pArray + pRootIndex + 1, len - pRootIndex - 1);

    return pRoot;
}

void destoryTree(binTree_t* pTree)
{
   if (pTree == NULL) {
        return; 
   } 
   destoryTree(pTree->left);
   destoryTree(pTree->right);
   free(pTree);
}

void printTree(binTree_t* pTree)
{
    if (pTree == NULL) {
        return; 
    }
    printTree(pTree->left);
    printTree(pTree->right);
    printf("%d ", pTree->value);
}

#if 1
enum WIDTH_MODE{
    LEFT,
    RIGHT
};
typedef enum WIDTH_MODE width_mode_e;
#endif

//static void getWidth(binTree_t* pTree, width_t** pHead)
static uint8_t getWidth(binTree_t* pTree, width_t** pHead)
{
    
}

void drawBranch(uint16_t x, uint16_t y, uint16_t *rx, uint16_t* ry, uint16_t height, width_mode_e mode)
{
    int i;

    if (mode == LEFT) {
        for (i = 0; i < height; i++) {
            terminal_draw_char(x, y, "/");
            x--; 
            y++;
        }
//        *rx = x + 1;
        *rx = x;
        *ry = y;
    } else if (mode == RIGHT) {
        for (i = 0; i < height; i++) {
            terminal_draw_char(x, y, "\\");
            x++; 
            y++;
        }
//        *rx = x -1;
        *rx = x;
        *ry = y;
    }
}

uint32_t getTreeHeight(binTree_t* pTree)
{
    uint32_t height;
    uint32_t lHeight;
    uint32_t rHeight;

    if (pTree == NULL) {
        return 0; 
    }

    lHeight = getTreeHeight(pTree->left);
    rHeight = getTreeHeight(pTree->right);

    height = (lHeight > rHeight ? lHeight : rHeight) + 1;

    return height;
}

void drawTree(uint16_t x, uint16_t y, binTree_t* pTree)
{
    char buf[10];
    uint16_t width;
    uint16_t lWidth;
    uint16_t rWidth;
    uint16_t rx;
    uint16_t ry;
    if (pTree == NULL) {
        return; 
    }
    memset(buf, 0, sizeof(buf));
    itoa(pTree->value, buf, 10);
    
    terminal_draw_char(x, y, buf);

    rWidth = getWidth(pTree->right, RIGHT);
    lWidth = getWidth(pTree->left, LEFT);
    width = rWidth > lWidth ? rWidth : lWidth;
    if (pTree->left) {
        drawBranch(x - 1, y + 1, &rx, &ry, width, LEFT);
        drawTree(rx, ry, pTree->left);
//        termial_draw_char(x - 1, y + 1, "/");
//        drawTree(x - 2, y + 2, pTree->left);
    }
    
    if (pTree->right) {
        drawBranch(x + 1, y + 1, &rx, &ry, width, RIGHT);
        drawTree(rx, ry, pTree->right);
//        termial_draw_char(x + 1, y + 1, "\\");
//        drawTree(x + 2, y + 2, pTree->right);
    }

}
