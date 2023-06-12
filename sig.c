#include "sig.h"
#include "proc.h"
#include <unistd.h>

// choose proper signal num for communication

void exitSigHandler_Proc(int sigNo){
    printf("sig %d\n", sigNo);
    destory();
    exit(0);
}

void exitSigHandler_Display(int sigNo){

}

// enable procinfo proc react to cmd from ui
void comSigHandler_Proc(int sigNo){

}

// enable ui proc to react to response from procinfo
void comSigHandler_Display(int sigNo){

}

void initSigMonitor_Proc(int sigNo){
}

void initSigMonitor_Display(int sigNo){
}