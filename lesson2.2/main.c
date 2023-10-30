#include "stdio.h"
#include "string.h"
#include "unistd.h" // lib used to declared flags of system call
#include "fcntl.h"
#include "sys/stat.h"
#include "sys/sysmacros.h"
#include "time.h"

/*Declared func*/
void getInfoFile (struct stat sb, const char *file_name);

int main(void)
{
    int fd;         // the return's value of fopen
    struct stat sb; // list of type's file
    const char *file_name = "helloworld.txt";
    int num_read, num_write;
    char* buf2 = "Messi 10 diem";
    char* buf3 = "ronaldo";
    
    // fd = open("helloworld.txt", O_APPEND | O_RDWR | O_CREAT, 0666);
    fd = open("helloworld.txt", O_RDWR, 0666); //open file, if it isn't exist, create a file with O_CREAT flag
    // add 'O_APPEND flag' which allows append sth inside file
    if (-1 == fd)
    {
        printf("check\n");
    }
    off_t cur = lseek (fd, 5, SEEK_SET);
    printf("Value cur of fd:                       %d\n",fd);
    write(fd, buf3, strlen(buf2));
    /*Write sth inside specific file*/
    // num_write = write(fd,buf,sizeof(buf)); //num_write will return bytes which it write into file 'fd'
    // printf("Write %d (num_write) bytes inside helloworld file", num_write);
    getInfoFile(sb,file_name);
    
    close(fd);
    return 0;
}

void getInfoFile (struct stat sb, const char *file_name){
    printf("Name of file:                        %s\n",file_name);
    /*Checking type of file using 'struct stat'*/
    if (stat(file_name, &sb) == 0)
    {
        mode_t file_type = sb.st_mode & __S_IFMT;
        printf("File's type:                         ");
        switch (sb.st_mode & __S_IFMT)
        {
        case __S_IFBLK:
            printf("block device\n");
            break;
        case __S_IFCHR:
            printf("character device\n");
            break;
        case __S_IFDIR:
            printf("directory\n");
            break;
        case __S_IFREG:
            printf("regular file\n");
            break;
        case __S_IFIFO:
            printf("FIFO\n");
            break;
        case __S_IFLNK:
            printf("Symbolic link\n");
            break;
        case __S_IFSOCK:
            printf("Socket\n");
            break;
        default:
            printf("unknown?\n");
            break;
        }
    }
    printf("Size file:                           %ld bytes\n",(__intmax_t) sb.st_size);
    printf("Last change action of file at:       %s", ctime(&sb.st_ctime));
    printf("Last file access:                    %s", ctime(&sb.st_atime));
    printf("Last file modification:              %s", ctime(&sb.st_mtime));
}   

