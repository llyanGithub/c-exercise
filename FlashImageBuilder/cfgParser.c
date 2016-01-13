#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include "common.h"
#include "cfgParser.h"

#define SUCCESS 0
#define FAIL 1

static uint16_t idCnt = 1;

typedef struct cfg_parser_s {
    uint8_t** key;    
    uint8_t** value;    
    uint16_t itmeCnt;
    uint16_t cfgId;
    struct cfg_parser_s* next;
} cfg_parser_s ;

typedef struct cfg_parser_s cfg_parser_t;

cfg_parser_t* head = NULL;

int16_t cfgParser_start(const uint8_t* fileName)
{
    cfg_parser_t* pCfg;
    FILE* fp;
    char buf[100];

    fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr, "%s: %s open failed\n", __FILE__, __LINE__); 
        return FAIL;
    }

    pCfg = (cfg_parser_t*)malloc(sizeof(cfg_parser_t)); 
    if (pCfg == NULL) {
        fprintf(stderr, "%s: %s malloc failed\n", __FILE__, __LINE__);
        return FAIL;
    }

    while (fgets(buf, sizeof(buf), fp)) {

    } 

}

uint8_t* cfgFileParser_getValue(uint16_t cfgId, const uint8_t* key)
{

}


int16_t cfgParser_end(const uint8_t* fileName)
{

}
