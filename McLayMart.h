/**McLay Mart Header file**/
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <errno.h>


//Prototypes
void initDataFile();
void readConfig();

//Defines
#define BUFFSIZE 10000

//Structs

struct dataLine
{
    char itemNum[32];
    char desc[128];
    char partNum[32];
};