#ifndef STAT_H_
#define STAT_H_
#include <dirent.h>
#include <unistd.h>
#include "uthash.h"

// const NAME_MAX = 254;

typedef struct ProcInfo{
    struct ProcInfo * next;
    char name[NAME_MAX+1];
    pid_t pid;
    pid_t ppid;
    size_t virt; //�����ڴ�
    size_t rss;  //פ����
    size_t shr;  //�����ڴ�
    size_t groupRss;
} ProcInfo;

typedef struct TreeNode {
    struct TreeNode * parent;
    struct TreeNode * child;
    struct TreeNode * next;
    ProcInfo * info;
    int generation;
} TreeNode;

typedef struct HashNode {
    pid_t id;
    TreeNode *value;
    UT_hash_handle hh;
} HashNode;

#endif