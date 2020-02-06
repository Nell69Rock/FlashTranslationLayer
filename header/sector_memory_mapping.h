#include "standard_flash_memory_io.h"



int SET_MAPPING_TABLE(int *mapping_table);
FLASH_MEMORY *FTL_WRITE(FLASH_MEMORY *SECTOR, int LSN, char data[]);
FLASH_MEMORY *FTL_READ(FLASH_MEMORY *SECTOR, int LSN);
FLASH_MEMORY *FTL_ERASE(FLASH_MEMORY *SECTOR, int LBN);

int *mapping_table = NULL;

