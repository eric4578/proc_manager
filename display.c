#include "display.h"
#include "stat.h"

// print mem size for man`s relish
// i.e. print it with different unit size like B KB MB and GB
// print and return the printed length
static inline size_t _display_memsz(size_t size){
    char * unit;
    // TODO
    // END of your code
    return printf("%ld%s ", size, unit);
}

static inline int _printProcInfo(const ProcInfo * info){
    size_t res = printf("-%s(%d,%d)[", info->name, info->pid, info->ppid);
    res += _display_memsz(info->virt);
    res += _display_memsz(info->rss);
    res += _display_memsz(info->shr);
    res += printf("] group:");
    res += _display_memsz(info->groupRss);
    return res+1;
}

// print proc tree with proper indentation
void printProcInfoTree(ProcInfo * info, int dep){
    // TODO
    // END
}