#ifndef SIG_H_
#define SIG_H_
#include <signal.h>

void sigHandler(int sigNo);

void initSigMonitor();

void timedTask(void (*fn)(void), int sec);

void exitSigHandler_Proc(int sigNo);

void exitSigHandler_Display(int sigNo);

void comSigHandler_Proc(int sigNo);

void comSigHandler_Display(int sigNo);

void initSigMonitor_Proc(int sigNo);

void initSigMonitor_Display(int sigNo);
#endif