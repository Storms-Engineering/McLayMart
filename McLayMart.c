#include "McLayMart.h"

char * returnItemInfo(char * itemNumber);
struct dataLine data[300];

int main()
{
    
    WINDOW *sub_window_ptr;
    
    char name[256],costCenter[256], items[256][256];
    //Curses init
    initscr();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2,COLOR_BLUE, COLOR_BLACK);
    init_pair(3,COLOR_RED, COLOR_BLACK);

    initDataFile();

    move(5,15);
    printw("%s", "Welcome to McClay Mart!");
    move(6,15);
    attrset(COLOR_PAIR(2));
    printw("Developed by Storms-Engineering");
    refresh();
    sleep(1);
    clear();


    move(0,0);
    attroff(COLOR_PAIR(2));
    printw("%s", "Name:");
    getstr(name);

    move(1,0);
    printw("%s", "Cost Center or AFE #:");
    getstr(costCenter);
    
    clear();
    move(0,0);
    printw("%s%s", "Name: ", name);

    move(0, 25);
    printw("%s%s", "Cost Center: ", costCenter);


    move(1,0);
    attrset(COLOR_PAIR(1));
    printw("%s", "Please Begin scanning");

    attroff(COLOR_PAIR(1));

    sub_window_ptr = subwin(stdscr, 40,200,2,0);
    scrollok(sub_window_ptr, 1);

    touchwin(stdscr);
    mvwprintw(sub_window_ptr, 0, 0, "Item #:             Description:");
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
        move(50,0);
        deleteln();
        refresh();

        //This will return a string line with item# and description of item
        strcpy(items[itemCount],returnItemInfo(item));
        mvwprintw(sub_window_ptr, ++itemCount, 0, items[itemCount]);
        wrefresh(sub_window_ptr);
        refresh();
    } 
    while (strlen(item) != 25);
    erase();
    refresh();


    //Curses destructor
    
    attron(A_BLINK | A_REVERSE);
    printw("END OF THE LINE.....\n");
    refresh();
    sleep(5);

    endwin();
    exit(EXIT_SUCCESS);
}




