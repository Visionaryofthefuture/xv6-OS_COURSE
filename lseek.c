#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

// Usage: ./lseek <filename> <offset> <whence> <newstring>
int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf(1, "usage: ./lseek <filename> <offset> <whence> <newstring>\n");
        exit();
    }
    
    int fd = open(argv[1], O_RDWR);    
    int offset = atoi(argv[2]);
    int whence;
    if (strcmp(argv[3], "SEEK_SET") == 0) {
        whence = SEEK_SET;
    } else if (strcmp(argv[3], "SEEK_CUR") == 0) {
        whence = SEEK_CUR;
    } else if (strcmp(argv[3], "SEEK_END") == 0) {
        whence = SEEK_END;
    }
    
    int ret = lseek(fd, offset, whence);
    if (ret < 0) {
        printf(1, "lseek failed\n");
        exit();
    }
    
    char *newString = argv[4];
    int len = strlen(newString);
    
    if (write(fd, newString, len) != len) {
        printf(1, "write failed\n");
        exit();
    }
    
    printf(1, "Successfully wrote '%s' at offset %d\n", newString, ret);
    
    close(fd);
    exit();
}
