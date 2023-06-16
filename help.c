#include"help.h"

#include<stdio.h>

void printUsage() {
    printf("Usage:\n");
    printf("\t -h --help\tShow help message.\n");
    printf("\t -p --showpids\tShow process IDs.\n");
    printf("\t -t --tree\tShow process trees.\n");
    printf("\t -s --sort\tShow processes.\n");
    printf("\t -v --version\tShow version information.\n");
}