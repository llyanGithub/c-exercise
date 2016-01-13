#ifndef __TREE_H
#define __TREE_H

#include "common.h"

struct binTree_s {
   uint32_t value;
   struct binTree_s* left;
   struct binTree_s* right;
};
typedef struct binTree_s binTree_t;

binTree_t* genTree(uint32_t* pArray, uint32_t len);

void destoryTree(binTree_t* pTree);
void printTree(binTree_t* pTree);
void drawTree(uint16_t x, uint16_t y, binTree_t* pTree);
#endif
