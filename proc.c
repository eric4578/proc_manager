#include "proc.h"
#include "stat.h"
#include "uthash.h"
#include "utils.h"
#include <alloca.h>
#include <assert.h>
#include <malloc.h>
#include "uthash.h"

ProcInfo * procInfoHash = NULL;

ProcInfo * createProcInfo(char * path, size_t pathLen){
    return NULL;
}

ProcInfo * updateProcInfo(ProcInfo * old, char * path, size_t pathLen){
    return NULL;
}

void freeNotAccessedProcInfo(){
}

ProcInfo * syncProcInfo(){
    return NULL;
}

// read the required info of one proc
ProcInfo * readProcStat(char * path, size_t pathLen){
    // TODO Level 1-1
    return NULL;
    // END of your code
}

// traverse all files in proc dir and put all of them in a linked list of Procinfo(next)
ProcInfo * readAllProcfs(){
    // TODO Level 1-1
    // open /proc dir and traverse the procfs
        // check if the subdir belong to proc
        // read details: readProcStat
    return NULL;
    // END of your code
}

// use hash to find the specified ProcInfo
ProcInfo * findProc(pid_t pid){
    // TODO Level 1-2
    return NULL;
    // END of your code
}

// set up ProcTree according to the ppid
// mind that root nodes are those with ppid 0
ProcInfo * createProcTree(ProcInfo * info){
    // TODO Level 1-2
    // END of your code
}

// free resources that you have alloced and earse the globals
__attribute__((destructor)) void destory(){
    // TODO Level ultraman
    // END of your code
}

// cal the total mem use of this proc and its children proc
size_t calProcGroupMemUse(ProcInfo * node){
    // TODO Level 1-3
    // END of your code
}

#define listProcInfo_Bro(info) do{}while(0)
#define listProcInfo_All(info) do{}while(0)
#define _listProcInfo_(scope) listProcInfo_##scope
#define listProcInfo_(scope, info) _listProcInfo_(scope)(info)

void sortProcInfo(ProcInfo * info){
}