/* McLayMart - A inventory management system.

Designed to be used with a barcode scanner to speed up process by entering information
about where the items are to be used, who they are checked out by, and then scanning all
the items that you want.  Then the system will send out an email detailing all the items checked out.

by Brayden Storms 1-1-23

*/

#include "McLayMart.h"

struct Part returnItemInfo(char * itemNumber);

//Items are the stuff users are checking out
struct Part *first_item;
struct Part *current_item;
struct Part *new_item;
char name[256],costCenter[256], items[256][256];

int main()
{
    
    WINDOW *sub_window_ptr;
    
    
    //Curses init
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2,COLOR_YELLOW, COLOR_BLACK);
    init_pair(3,COLOR_RED, COLOR_BLACK);
    init_pair(4,COLOR_BLUE, COLOR_BLACK);

    initDataFile();

    move(5,15);
    printw("%s", "Welcome to McClay Mart!");
    move(6,15);
    attrset(COLOR_PAIR(4));
    printw("Developed by Storms-Engineering");
    beep();
    refresh();
    sleep(1);
    clear();

    //Main loop
    while(true)
    {
        move(0,0);
        attroff(COLOR_PAIR(2));
        printw("%s", "Name:");
        getstr(name);
        deleteln();
        refresh();
        move(0,0);
        //TODO make this part of the config file that has a list of the cost centers you want and the corresponding numbers
        printw("%s", "Cost Center or AFE #");
        char *choices[] = {"Kenai Gas Field", "Cannery Loop", "Beaver Creek", "Ninilchik", "AFE #/Cost Center", NULL};
        char * costCenters[] = {"900000202", "999908880", "123456789", "12234561111", NULL};
        printList(1, choices);
        printw("\nYour choice:");
        refresh();
        char choice[256];
        getstr(choice);
        //Custom choice
        if(costCenters[atoi(choice)] == NULL)
        {
            clear();
            mvprintw(0,0,"Enter AFE # or Cost Center:");
            refresh();
            getstr(costCenter);
        }
        else
        {
            strcpy(costCenter,costCenters[atoi(choice)]);
        }
        clear();
        move(0,0);
        printw("Name:%s", name);

        move(0, 25);
        printw("Cost Center:%s", costCenter);

        msg("Please begin scanning", MSGLVL_INFO);
        mvprintw(2, 0, "Item #:                  Description:");
        mvprintw(3,0,  "-------------------------------------");
        sub_window_ptr = subwin(stdscr, 40,200,4,0);
        //scrollok(sub_window_ptr, 1);

        touchwin(stdscr);
        wrefresh(sub_window_ptr);
        refresh();
        int itemCount = 0;
        char item[256];
        do
        {
            move(50,0);
            printw("Item #:");
            //Adding items
            getstr(item);
            strcpy(item,removeChar(item, '-'));
            move(50,0);
            deleteln();
            refresh();
            //Initiate first item in list     
            if(first_item == NULL)
            {
                first_item = (struct Part *)malloc(sizeof(struct Part));
                current_item = first_item;
            }
            *current_item = returnItemInfo(item);
            //If part doesn't exist, skip the rest and start over
            if(strcmp(current_item->itemNum,"NULL") == 0)
                continue;
            mvwprintw(sub_window_ptr, itemCount, 0, current_item->partNum);
            mvwprintw(sub_window_ptr, itemCount++, 25, current_item->desc);
            wrefresh(sub_window_ptr);
            refresh();
            new_item = (struct Part *)malloc(sizeof(struct Part));
            current_item->next = new_item;
            current_item = new_item; 
        } 
        //Apparently the string length includes other things *shrug*
        while (strlen(item) != 25);
        erase();
        //Curses destructor
        printw("Updating checked out item database......");
        updateDatabase();
        refresh();
    }
    

    endwin();
    exit(EXIT_SUCCESS);
}

void updateDatabase()
{
    FILE *checkoutDB;
    checkoutDB = fopen("checkoutDB.csv","a");
    
    if(!checkoutDB)
    {
        msg(MSGLVL_ERR,"CRITICAL ERROR WITH CHECKOUT DB.... ALERT THE MASTER!");
    }
    struct Part *prev_item;
    //start at the beginning
    current_item = first_item;
    while(current_item)
    {
        //Data is organized: DNOW (SAP) item #, Description, Part #, Name, Cost Center
        fprintf(checkoutDB,"%s,%s,%s,%s,%s\n", current_item->itemNum, current_item->desc, current_item->desc, name, costCenter);
        prev_item = current_item;
        current_item = current_item->next;
        //Start cleaning up memory
        free(prev_item);
    }
    //Free the first item
    free(first_item);
    fclose(checkoutDB);
}




