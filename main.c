#include "proc.h"
#include "utils.h"
#include "display.h"
#include "help.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>

//stop signal
int stopped = 0;
//init thread
pthread_t thread_scan, thread_UI, thread_c;
//init semaphore
sem_t sem_scan, sem_UI, sem_scanning;

ProcInfo * LinkHead;
TreeNode * root;

void *threadFuncScan() {
    int res =-1;
    // pthread_sigmask(SIG_BLOCK,&set,NULL);
    for(;;){
        sem_wait(&sem_scan);
        //锁
        res = sem_init(&sem_scanning, 0, 0);
        printf("Scanning\n");
        LinkHead = readAllProcfs();
        root = readProcTree(LinkHead);
        sleep(5);//模拟保护
        res = sem_init(&sem_scan, 0, 0);
	    if(res == -1)
	    {
		    perror("semaphore scan intitialization failed\n");
		    exit(EXIT_FAILURE);
        }
        sem_post(&sem_scanning);
    }
}

void *threadFuncUI() {
    int scanning = -1;
    int res =-1;
    // pthread_sigmask(SIG_BLOCK,&set,NULL);
    for(;;){
        sem_wait(&sem_UI);
        sem_getvalue(&sem_scanning, &scanning);
        if (!scanning)  printf("waiting scan....\n");
        sem_wait(&sem_scanning);
        printf("UI\n");
        res = sem_init(&sem_UI, 0, 0);
	    if(res == -1)
	    {
		    perror("semaphore scan intitialization failed\n");
		    exit(EXIT_FAILURE);
        }
    }
}

void sigint_handler(int sig){
	if(sig == SIGINT){
		printf("ctrl+c pressed!\n");
		stopped = 1;
	}
}

int main(int argc, char * argv[]){
    signal(SIGINT, sigint_handler);

    LinkHead = readAllProcfs();
    root = readProcTree(LinkHead);

    int res = -1;

    //init sem
    res = sem_init(&sem_scan, 0, 0);
	if(res == -1)
	{
		perror("semaphore scan intitialization failed\n");
		exit(EXIT_FAILURE);
    }

    res = sem_init(&sem_UI, 0, 0);
	if(res == -1)
	{
		perror("semaphore scan intitialization failed\n");
		exit(EXIT_FAILURE);
    }

    res = sem_init(&sem_scanning, 0, 0);
	if(res == -1)
	{
		perror("semaphore scanning intitialization failed\n");
		exit(EXIT_FAILURE);
    }
    sem_post(&sem_scanning);
    // end of sem

    res = pthread_create(&thread_scan, NULL, threadFuncScan, NULL);
    res = pthread_create(&thread_UI, NULL, threadFuncUI, NULL);

    int flag1, flag2;
    if(flag1=(fcntl(STDIN_FILENO, F_GETFL, 0)) < 0)
    {
        perror("fcntl");
        return -1;
    }
    flag2 = flag1 | O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flag2);

    int ret;
    char p;
    while(1)
    {
        // fflush(stdin);
        if (stopped) {
            destoryProcLink(LinkHead);
            break;
        }
        sleep(1);
        LinkHead = readAllProcfs();
        root = readProcTree(LinkHead);
        time_t now = time(NULL);
        char time_str[20];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M", localtime(&now));
        printf("%s\n", time_str);
        ret = scanf("%c", &p);
        if (ret > 0) {
            if (p == 'p') {
                printProcLink(LinkHead);
            }
            if (p == 't') {
                printProcTree(root);
            }
            if (p == 'h') {
                printUsage();
            }
            if (p == 's') {
                sem_post(&sem_scan);
            }
            if (p == 'u') {
                sem_post(&sem_UI);
            }
        } else {
            printf("--------------\n");
        }

        // printf("%d",  feof(stdin)); //0

        // if(! feof (stdin)){
        //     if ((p=getchar()) == 'p') {
        //         printProcLink(LinkHead);
        //         sleep(1);
        //     }
        //     continue;
        // } else {
        //     break;
        // }
    }
    return 0;
}
    // while (1)
    // {
    //     ProcInfo * LinkHead = readAllProcfs();
    //     TreeNode * root = readProcTree(LinkHead);
    // }

    // int ret = 0;
    // while ((ret = getopt(argc, argv, "hptsv")) != -1)
    // {  
    //     switch (ret)
    //     {
    //     case 'h':
    //         printUsage();
    //         break;
    //     case 'p':
    //         printProcLink(LinkHead);
    //         break;
    //     case 't':
    //         printProcTree(root);
    //         break;
    //     default:
    //         //TODO 报错处理
    //         break;
    //     };
    //     printf("optarg = %s\t\t", optarg);
    //     printf("optind = %d\t\t", optind);
    //     printf("argv[optind] = %s\n", argv[optind]);
    // }

    // // ProcInfo* LinkHead = readAllProcfs();
    // // printf("debug\n");

    // return 0;

