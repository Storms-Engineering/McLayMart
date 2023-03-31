#include "McLayMart.h"

struct Part *first_part;
struct Part *current_part;
struct Part *new_part;


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
        refresh();
        sleep(3);
        //Exit with file does not exist status
        exit(ENOENT);
    }
    char line[BUFFSIZE];


    
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
        printError("ERROR: data.csv not found, please provide a database file");
        move(1,0);
        printw("Exiting....");
        refresh();
        sleep(3);
        //Exit with file does not exist status
        exit(ENOENT);
    }
    char line[BUFFSIZE];
    first_part = (struct Part *)malloc(sizeof(struct Part));
    current_part = first_part;


    //Read in file line by line
    while(fgets(line, BUFFSIZE, dataFile))
    {
        //Data is organized: DNOW (SAP) item #, Description, Part #
        strcpy(current_part->itemNum,strtok(line,","));
        strcpy(current_part->desc,strtok(NULL,","));
        strcpy(current_part->partNum,strtok(NULL,","));

        new_part = (struct Part *)malloc(sizeof(struct Part));
        current_part->next = new_part;
        current_part = new_part;        
    }
    current_part->next = NULL;

    printw("Done");
    erase();
}

//Returns the part struct for the corresponding item #
//Returns null in itemNum if item cannot be found
struct Part returnItemInfo(char* itemNumber)
{
    struct Part tmpPart;
    //start at the beginning
    current_part = first_part;
    while(current_part)
    {
        if(!strcasecmp(itemNumber,current_part->itemNum) || !strcasecmp(itemNumber,current_part->partNum))
        {
            tmpPart = *current_part;
            msg("Item found", MSGLVL_INFO);
            break;
        }
        current_part = current_part->next;
        if(!current_part)
        {
            msg("Item not found!", MSGLVL_ERR);
            //Item not found.
            strcpy(tmpPart.itemNum,"NULL");
        }
    }
    return tmpPart;
}

void printList(int startLine, char * choices[])
{
    //puts(choices[1]);
    int i = 0;
    while(choices[i])
    {
        mvprintw(startLine + i,0,"(%i) ", i );
        printw(choices[i]);
        i++;
    }
}

void printError(char * errMsg)
{
    erase();
    move(0,0);
    attrset(COLOR_PAIR(1));
    printw(errMsg);
}

//Puts a message in the status bar
//Types of messages include: ERR, INFO, ALERT
//Err is red and is meant for critical things
//Info is green and are good status messages
//Alert is yellow and means something of note
void msg(char * msg, int msgLvl)
{
    move(MSGLINENUM,0);
    deleteln();
    insertln();
    attrset(COLOR_PAIR(msgLvl));
    printw(msg);
    attroff(COLOR_PAIR(msgLvl));
    if(msgLvl > 1)
        beep();
    refresh();
}

//Takes a string and modifies it so that the original string does not contain the character specified toRemove and returns it
//Could be upgraded to remove a string instead of a character by using strlen and looking through blocks at a time
char *removeChar(char * origString, char toRemove)
{
    static char tmpString[256];
    int i = 0;
    while(*origString)
    {
        if(*origString != toRemove)
        {
            tmpString[i] = *origString;
            i++;
        } 
        origString++;
    }
    return tmpString;
}

