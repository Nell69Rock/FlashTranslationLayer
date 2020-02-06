#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SECTOR_SIZE 512
#define META_DATA 16
#define NUM_OF_SECTOR 32
#define NUM_OF_BLOCK 64

typedef struct
{
    char sector[SECTOR_SIZE];
    char metadata[META_DATA];
}FLASH_MEMORY;



void filesave(FLASH_MEMORY *SECTOR);
int filecheck();
FLASH_MEMORY *loaddata();

FLASH_MEMORY *init();
FLASH_MEMORY *flash_write(FLASH_MEMORY *SECTOR, int PSN, char data[]);
FLASH_MEMORY *flash_erase(FLASH_MEMORY *SECTOR, int BLOCK);

void flash_read(FLASH_MEMORY *SECTOR, int PSN);
void flash_print(FLASH_MEMORY *SECTOR);
int get_block(int PSN);
void cleardisplay();


int totalsector;