#ifndef STAT_H_
#define STAT_H_
#include "uthash.h"
#include <dirent.h>
#include <unistd.h>

typedef struct ProcInfo{
    struct ProcInfo * next;
    char name[NAME_MAX+1];
    pid_t pid;
    pid_t ppid;
    size_t virt;
    size_t rss;
    size_t shr;
    size_t groupRss;
} ProcInfo;

#endif