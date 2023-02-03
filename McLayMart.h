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
void msg(char *);

//Defines
#define BUFFSIZE 10000
#define MSGLINENUM 2
#define ERR 0
#define INFO 1
#define ALERT 2


//Structs

struct Part
{
    char itemNum[32];
    char desc[128];
    char partNum[32];
    struct Part *next;
};