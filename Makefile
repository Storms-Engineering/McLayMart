#Makefile for McLay Mart program

McLayMart: McLayMart.o util.o
	gcc McLayMart.o util.o -o McLayMart -lcurses

McLayMart.o: McLayMart.c util.c
	gcc -c McLayMart.c -lcurses

util.o: util.c
	gcc -c util.c -lcurses