/**McLay Mart Header file**/
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <errno.h>


//Prototypes
void initDataFile();
void readConfig();
void printList(int startLine, char * choices[]);
void printError(char * errMsg);
void msg(char *, int msgLevel);
char *removeChar(char * origString, char toRemove);
void updateDatabase();

//Defines
#define BUFFSIZE 10000
#define MSGLINENUM 1

#define MSGLVL_INFO 1
#define MSGLVL_ALERT 2
#define MSGLVL_ERR 3


//Structs

struct Part
{
    char itemNum[32];
    char desc[128];
    char partNum[32];
    struct Part *next;
};