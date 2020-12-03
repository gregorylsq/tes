#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

static char usrdata[]={"hello device"};

int main(int argc, char *argv[]) {

    int fd, retvalue;
    char *filename;

    char readbuf[100],writebuf[100];

    if(argc!=3)
    {
        printf("error use");
        return -1;
    }

    filename = argv[1];

    fd=open(filename,O_RDWR);

    if(fd<0)
    {
        printf("cannot open file");
        return -1;
    }
    else
    {
        printf("open success\r\n");
    }
    

    if(atoi(argv[2])==1)
    {
        retvalue = read(fd,readbuf,50);
        if (retvalue<0)
        {
            printf("read %s fail\r\n",filename);
        }
        else
        {
            printf("read data %s\r\n",readbuf);
        }   
    }

    if(atoi(argv[2])==2)
    {
        memcpy(writebuf,usrdata,sizeof(usrdata));
        retvalue = write(fd,writebuf,50);
        if(retvalue<0)
            printf("write fail\r\n");
        else
        {
            printf("write success\r\n");
        }
        
    }

    retvalue = close(fd);
    if(retvalue<0)
    {
        printf("clsoe file fail\r\n");
        return -1;
    }
    return 0;
}