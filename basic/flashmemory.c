#include "../header/standard_flash_memory_io.c"

FLASH_MEMORY *precondition();
void *run(FLASH_MEMORY *SECTOR);
void *teardown(FLASH_MEMORY *SECTOR);

int main()
{
    FLASH_MEMORY *SECTOR = NULL;

    SECTOR = precondition();
    run(SECTOR);
    teardown(SECTOR);
}




FLASH_MEMORY *precondition()
{
    FLASH_MEMORY *tempsector = NULL;

	char yesorno[10];
	int check = filecheck();

	if(check == 0)
	{
		printf("The flash memory created previously exists.\nDo you want to continue? (yes/no)");
		scanf("%s", yesorno);
	}
	else
	{
		while((tempsector = init()) == NULL);
		return tempsector;
	}

	if(check == 0 && strcmp(yesorno, "no") == 0)
	{
		while((tempsector = init()) == NULL);
	}
	else if(check == 0 && strcmp(yesorno, "yes") == 0)
	{
		tempsector = loaddata();
	}
	else
	{
		printf("[ERROR] Wrong answer insert, please Re-try <ENTER>\n");
		cleardisplay();
		return precondition();
	}

    return tempsector;
}



void *run(FLASH_MEMORY *SECTOR)
{
	
	char select[30];
    while (1)
    {
        printf("PSN => Physical Sector Number.\n");
        printf("block => Sets of sector.\nthis simulator has 32 sector per 1 block.\n");
		printf("there are %d Sectors, there are %d blocks\n\n", totalsector, totalsector/NUM_OF_SECTOR);
        printf("==USAGE COMMAND==\n\n");
        printf("wtite [PSN] [DATA] \n");
        printf("read [PSN] \n");
        printf("erase [BLOCK] \n");
        printf("printsector \n");
        printf("exit \n\n");
        printf(">>> ");
        scanf("%s", select);
        
        if(strcmp("write", select) == 0)
        {
            int psn = 0;
            char data[SECTOR_SIZE];
            
            scanf("%d", &psn);
            scanf("%s", data);
            flash_write(SECTOR, psn, data);
        }
		else if(strcmp("read", select) == 0)
        {
            int psn = 0;
            scanf("%d", &psn);
            flash_read(SECTOR, psn);
        }
        else if(strcmp("erase", select) == 0)
        {
            int blockNumber = 0;
            scanf("%d", &blockNumber);
            flash_erase(SECTOR, blockNumber);
        }
		else if(strcmp("printsector", select) == 0)
		{
			flash_print(SECTOR);
		}
        
        else if(strcmp("exit", select) == 0)
        {
            printf("Program EXIT!\n");
            break;
        }
        else
        {
            printf("\n[ERROR] Unknown Input Error\n\n");
			cleardisplay();
        }
    }
	return 0;
}


void *teardown(FLASH_MEMORY *SECTOR)
{
	filesave(SECTOR);
}