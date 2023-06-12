#include "proc.h"
#include "stat.h"
#include "utils.h"
#include <alloca.h>
#include <assert.h>
#include <malloc.h>

static const size_t BLOCKNUM = 600; // should be a bit more than commonly running proc num
static size_t infoBufInd;
static size_t infoBufSize; 
static ProcInfo * infoBuf[2] = {0};
typedef struct MemHeadBuf{
    ProcInfo * head;
    struct MemHeadBuf * next;
} MemHeadBuf;
static MemHeadBuf * memHeadBuf = NULL;

void initProcInfo(){
    assert(BLOCKNUM >> 2 > 0);
    mallopt(M_MMAP_MAX, 0); // no mmap for malloc
    mallopt(M_TRIM_THRESHOLD, -1); // no memory compaction

    // TODO Level memManagment
    // END of your code
}

ProcInfo * allocProcInfo(){
    // TODO Level memManagment
    return NULL;
    // END of your code
}

// store free ProcInfo block
void freeProcInfo(ProcInfo * info){
    // TODO Level memManagment
    // END of your code
}

// free all alloced memory area
void destoryMem(){
    // TODO Level memManagment
    // END of your code
}