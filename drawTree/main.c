#include "common.h"
#include "tree.h"

int main(int argc, char* argv[])
{
    uint32_t buf[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    binTree_t* pTree;

    termial_init();
    pTree = genTree(buf, sizeof(buf) / 4);
//    printTree(pTree);
//    printf("\n");
    drawTree(40, 10, pTree);


    return 0;
}
