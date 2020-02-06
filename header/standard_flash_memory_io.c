#include "standard_flash_memory_io.h"


void filesave(FLASH_MEMORY *SECTOR)
{
	FILE *fp = NULL;
	FLASH_MEMORY data;
	int i = 0;
	if ((fp = fopen("FlashMemory.dat", "wb+")) == NULL) 
	{ 
		fprintf(stderr, "Not allowed File OPEN/CREATE");
		exit(1);
	}
	fseek(fp, 0, SEEK_SET);	
	for(i = 0; i < totalsector; i++)
	{
		strcpy(data.sector, SECTOR[i].sector);
		strcpy(data.metadata, SECTOR[i].metadata);
		fwrite(&data, sizeof(data), 1, fp);
	}
	fclose(fp);
}

int filecheck()
{
	FILE *fp = NULL;
	if ((fp = fopen("FlashMemory.dat", "rb+")) == NULL) 
	{
		printf("you have not FlashMemory Initalized program execution \n");
		return -1;
	}
	fclose(fp);
	return 0;
}

FLASH_MEMORY *loaddata()
{
	FILE *fp = NULL;
	FLASH_MEMORY data;
	FLASH_MEMORY *load_sector;
	int i = 0;
	totalsector = 0;
	if ((fp = fopen("FlashMemory.dat", "rb+")) == NULL) 
	{ 
		if ((fp = fopen("FlashMemory.dat", "wb+")) == NULL) 
		{ 
			fprintf(stderr, "Not allowed File OPEN/CREATE");
			exit(1);
		}
	}
	fseek(fp, 0, SEEK_SET);
	while (fread(&data, sizeof(data), 1, fp)) // 파일의 끝까지 반복
	{
		totalsector++;
	}

	
	load_sector = (FLASH_MEMORY *)malloc(sizeof(FLASH_MEMORY) * (totalsector));
	printf("there are %d Sectors, there are %d blocks\n\n", totalsector, totalsector/NUM_OF_SECTOR);

	fseek(fp, 0, SEEK_SET);
	for(i = 0; i < totalsector; i++)
	{
		fread(&data, sizeof(data), 1, fp);
		strcpy(load_sector[i].sector, data.sector);
		strcpy(load_sector[i].metadata, data.metadata);
	}
	fclose(fp);
	return load_sector;
}

FLASH_MEMORY *init()
{
    FLASH_MEMORY *temp_sector = NULL;
    int megabyte;
	int i = 0;


    printf("Flash Memory Apps. Made By Seok-Bin seo.\n");
    printf("Enter the megabytes to initialize >>>>");
	scanf("%d", &megabyte);
    if(megabyte <= 0)
    {
        printf("[ERROR] Wrong number insert, please Re-try <ENTER>\n");
		cleardisplay();
        return NULL;
    }
    

    totalsector = NUM_OF_SECTOR * NUM_OF_BLOCK * megabyte;
	temp_sector = (FLASH_MEMORY *)malloc(sizeof(FLASH_MEMORY) * (totalsector));

    for(i = 0; i < totalsector; i++)
    {
        strcpy(temp_sector[i].sector, "-1");
        strcpy(temp_sector[i].metadata, "-1");
    }
	printf("Initialize %dMB, there are %d Sectors, there are %d blocks <ENTER> \n\n",megabyte, totalsector, totalsector/NUM_OF_SECTOR);
    cleardisplay();
	return temp_sector;
}
FLASH_MEMORY *flash_write(FLASH_MEMORY *SECTOR, int PSN, char data[])
{
    int blockLocation = 0;
    if(PSN >= totalsector)
    {
        printf("\n[ERROR] Out of sector <ENTER>\n\n");
		cleardisplay();
        return SECTOR;
    }
    blockLocation = get_block(PSN);
    if(strcmp(SECTOR[PSN].sector, "-1") == 0)
    {
        strcpy(SECTOR[PSN].sector, data);
        printf("Data insert Success\n");
        printf("[%d]Sector ==> %s\n", PSN, data);
        printf("block number is ==> %d <ENTER>\n", blockLocation);
		cleardisplay();
    }
    else
    {
        printf("[ERROR] Data insert Fail\n");
        printf("[%d]Sector has Already data!\n", PSN);
        printf("[%d]Sector==> %s\n", PSN, SECTOR[PSN].sector);
        printf("block number is ==> %d <ENTER>\n", blockLocation);
		cleardisplay();
    }
    return SECTOR;
}
void flash_read(FLASH_MEMORY *SECTOR, int PSN)
{
    if(PSN >= totalsector)
    {
        printf("\n[ERROR] Out of sector <ENTER>\n\n");
		cleardisplay();
    }
    if(strcmp(SECTOR[PSN].sector, "-1") == 0)
    {
        printf("[%d]Sector == EMPTY <ENTER> \n", PSN);
		cleardisplay();
    }
    else
    {
        printf("[%d]Sector == %s <ENTER> \n", PSN, SECTOR[PSN].sector);
		cleardisplay();
    }
}
int get_block(int PSN)
{
	int i = 0;
	for(i = 0; i < totalsector/NUM_OF_SECTOR; i++)
    {
        if(PSN > (NUM_OF_SECTOR * i) && PSN <= (NUM_OF_SECTOR * (i+1)))
        {
            PSN = i;
            break;
        }
    }
    return PSN;
}

FLASH_MEMORY *flash_erase(FLASH_MEMORY *SECTOR, int BLOCK)
{
    char empty[SECTOR_SIZE] = "-1";
	int i = 0;

	int startSECTOR = BLOCK * NUM_OF_SECTOR;
    int endSECTOR = startSECTOR + NUM_OF_SECTOR;

	if(BLOCK > totalsector/NUM_OF_SECTOR)
    {
        printf("\n[ERROR] Out of Block <ENTER>\n\n");
		cleardisplay();
        return SECTOR;
    }
	
        
    for(i = startSECTOR; i < endSECTOR; i++)
    {
        strcpy(SECTOR[i].sector, empty);
    }
    printf("\n%d Block`s Erased!!!! <ENTER>\n", BLOCK);
	cleardisplay();
    return SECTOR;
}

void flash_print(FLASH_MEMORY *SECTOR)
{
	int i = 0;
    for(i = 0; i < totalsector; i++)
    {
        if(strcmp(SECTOR[i].sector, "-1") == 0)
        {
            printf("[%d]Sector == EMPTY\n", i);
        }
        else
        {
            printf("[%d]Sector == %s\n",i ,SECTOR[i].sector);
        }
    }
    return;
}

void cleardisplay()
{
	fflush(stdin);
	system("PAUSE");
	system("cls");
}
