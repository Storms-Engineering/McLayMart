#include "McLayMart.h"

extern struct dataLine data[300];

//Opens config file and reads parameters
void readConfig()
{
    printw("Reading config...");
    FILE * dataFile;
    dataFile = fopen(".config", "r");
    if(!dataFile)
    {
        erase();
        move(0,0);
        attrset(COLOR_PAIR(1));
        printw("ERROR: data.csv not found, please provide a database file");
        move(1,0);
        printw("Exiting....");
        sleep(3);
        //Exit with file does not exist status
        exit(ENOENT);
    }
    char line[BUFFSIZE];
    int datPosition = 0;
   
    //Read in file line by line
    while(fgets(line, BUFFSIZE, dataFile))
    {
        //Data is organized: DNOW (SAP) item #, Description, Part #
        strcpy(data[datPosition].itemNum,strtok(line,","));
        strcpy(data[datPosition].desc,strtok(NULL,","));
        strcpy(data[datPosition].partNum,strtok(NULL,","));
        datPosition++;
    }
    printw("Done");
    erase();
}

void initDataFile()
{
    printw("Reading database...");
    FILE * dataFile;
    dataFile = fopen("data.csv", "r");
    if(!dataFile)
    {
        erase();
        move(0,0);
        attrset(COLOR_PAIR(1));
        printw("ERROR: data.csv not found, please provide a database file");
        move(1,0);
        printw("Exiting....");
        sleep(3);
        //Exit with file does not exist status
        exit(ENOENT);
    }
    char line[BUFFSIZE];
    int datPosition = 0;
   
    //Read in file line by line
    while(fgets(line, BUFFSIZE, dataFile))
    {
        //Data is organized: DNOW (SAP) item #, Description, Part #
        strcpy(data[datPosition].itemNum,strtok(line,","));
        strcpy(data[datPosition].desc,strtok(NULL,","));
        strcpy(data[datPosition].partNum,strtok(NULL,","));
        datPosition++;
    }
    printw("Done");
    erase();
}

//Dummy function for now
char * returnItemInfo(char* itemNumber)
{
    
    return strcat(itemNumber,"              Description");
}