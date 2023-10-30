#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
/*
    function check parameter that was put into main.c
    argc is a interger, that is numbers of parameters
    argv is const pointer, that is title of each argc
*/

// cmd test: ./exe/run run1 run2 run3 => run is exe file after build this file
void main(int argc, char const *argv[]){
    
    int number;
    printf ("Number of parameters: %d\n", argc);
    for (int i=0;i<argc;i++){
        printf("argc[%d] = %s\n",i,argv[i]);
    }
}