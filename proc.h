#ifndef PROC_H_
#define PROC_H_
#include "stat.h"
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/io.h>

#define READBUFSIZE (256)
static char readBuf[READBUFSIZE];

/***************************/ 
void initProcInfo();

ProcInfo * allocProcInfo();

void freeProcInfo(ProcInfo * info);

void destoryMem();
/***************************/ 

/***************************/ 
ProcInfo * readProcStat(char * path, size_t pathLen);

ProcInfo * readAllProcfs();

ProcInfo * findProc(pid_t pid);

ProcInfo * createProcTree(ProcInfo * info);

size_t calProcGroupMemUse(ProcInfo * node);

ProcInfo * syncProcInfo();

void destory();
/***************************/ 

#endif
