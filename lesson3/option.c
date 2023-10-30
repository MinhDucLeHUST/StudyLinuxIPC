#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main(int argc, char const* argv[]){
    printf("Run cmd ls after 2s");
    sleep(2);
    execl("/usr/bin/ls", "ls", "-l", "-a", "-h", NULL);
    return 0;
}