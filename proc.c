#include "proc.h"
#include "stat.h"
#include "utils.h"
#include "uthash.h"
#include <alloca.h>
#include <assert.h>
#include <malloc.h>
#include <sys/types.h>   
#include <dirent.h>
#include <stdio.h>

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
    DIR *ProcDir;
    if ((ProcDir = readdir(path) == NULL)) {
        printf("error:proc dir does not exist!");
    }

    closedir(ProcDir);
    ProcInfo* proc = (ProcInfo *)malloc(sizeof(ProcInfo));
    
    
    return NULL;
    // END of your code
}

// traverse all files in proc dir and put all of them in a linked list of Procinfo(next)
// 返回进程链表
ProcInfo * readAllProcfs(){
    // TODO Level 1-1
    // open /proc dir and traverse the procfs
        // check if the subdir belong to proc
        // read details: readProcStat

    // 创建头指针
    ProcInfo* current = (ProcInfo *)malloc(sizeof(ProcInfo));
    ProcInfo* head = current;

    DIR *procdir;
    FILE *fp;
    struct dirent *entry;
    char path[256 + 5 + 5]; // d_name + /proc + /stat
    pid_t pid;
    pid_t ppid;
    size_t virt; //虚拟内存
    size_t rss;
    unsigned long maj_faults;

    procdir = opendir(DIRPATH);
    if (!procdir) {
        printf("error open dir /proc!");
    }
 
    while ((entry = readdir(procdir))) {
        // Skip anything that is not a PID folder.

        if (!is_pid_folder(entry)){
            continue;
        }
        // Try to open /proc/<PID>/stat.
        snprintf(path, sizeof(path), "/proc/%s/stat", entry->d_name);

        fp = fopen(path, "r");
 
        if (!fp) {
            perror(path);
            continue;
        }
 
        // Get PID, process name and number of faults.
        fscanf(fp, "%d %s %*c %d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu %*lu %*lu %*lu %*lu %*d %*lu %*lu %*lu %*lu %lu %u, %*lu",
            &pid, &path, &ppid, &virt, &rss
        );
 
        // Pretty print.
        // printf("%5d %-20s: %lu %lu %lu\n", pid, path, ppid, virt, rss);

        //链表插入
        ProcInfo* proc = (ProcInfo *)malloc(sizeof(ProcInfo));
        proc->next = NULL;
        proc->pid = pid;
        proc->ppid = ppid;
        proc->virt = virt;
        proc->rss = rss;
        strcpy(proc->name, path);

        current->next = proc;
        current = current->next;

        fclose(fp);
    }

    ProcInfo* iter = head->next;


    // printf("done\n");
    return head->next;
     // END of your code
}

void printProcLink(ProcInfo *LinkHead){
    ProcInfo *iter = LinkHead;
    while (iter != NULL) {
        printf("%5d %-20s: %d %lu %lu\n", iter->pid, iter->name, iter->ppid, iter->virt, iter->rss);
        iter = iter->next;
    }
}
// 如果ppid大于当前pid，则一定在树中
// 查询父进程进程位置
// 插入进程
TreeNode * readProcTree(ProcInfo *LinkHead) {
    HashNode *HashMap = NULL;

    // 获取ppid
    TreeNode* root = (TreeNode *)malloc(sizeof(TreeNode));
    root->child = NULL;

    ProcInfo* iter = LinkHead;
    while (iter != NULL) {
        // printf("%5d %-20s: %d %lu %lu\n", iter->pid, iter->name, iter->ppid, iter->virt, iter->rss);
        TreeNode* n = (TreeNode *)malloc(sizeof(TreeNode));    
        if(iter->ppid == 0) {
            n->info = iter;
            n->child = NULL;
            n->generation = 1;
            n->parent = root;
            // printf("debug1\n");
            if (root->child == NULL) {
                root->child = n;
                n->next = NULL;
                // printf("debug2\n");
            } else {
                TreeNode *NodeIter = root->child;
                if (NodeIter == NULL){
                    root->child = n;
                }
                while (NodeIter->next != NULL){
                    NodeIter = NodeIter->next;
                }
                NodeIter->next = n;
                n->next = NULL;
            }   
        } else {
            HashNode *h;
            HASH_FIND_INT(HashMap, &(iter->ppid), h);
            TreeNode* ParentNode = h->value;
            // printf("%5d %-20s: %d %lu %lu\n", ParentNode->info->pid, 
                // ParentNode->info->name, ParentNode->info->ppid, ParentNode->info->virt, ParentNode->info->rss);
            n->info = iter;
            n->child = NULL;
            n->generation = ParentNode->generation + 1;
            n->parent = ParentNode;
            // printf("debug8\n");

            if (ParentNode->child == NULL) {
                ParentNode->child = n;
                n->next = NULL;
                // printf("debug9\n");
            } else {
                TreeNode *NodeIter = ParentNode->child;
                if (NodeIter == NULL){
                    ParentNode->child = n;
                }
                while (NodeIter->next != NULL){
                    ProcInfo* p = NodeIter->info;
                    // printf("%5d %-20s: %d %lu %lu\n", p->pid, p->name, p->ppid, p->virt, p->rss);
                    NodeIter = NodeIter->next;
                }
                // if (NodeIter == NULL) {
                //     printf("yes NULL1\n");
                // }
                NodeIter->next = n;
                if (NodeIter == NULL) {
                    // printf("yes NULL1\n");
                }
                n->next = NULL;
            }    
        }

        HashNode *h;
        HASH_FIND_INT(HashMap, &(iter->pid), h);
        // printf("debug4\n");
        if (h == NULL) {
            h = (HashNode *)malloc(sizeof(HashNode));
            h->id = iter->pid;
            h->value = n;
            // printf("debug5\n");
            HASH_ADD_INT(HashMap, id, h);
        }
        // printf("debug6\n");

        iter = iter->next;
        // printf("debug7\n");
    }
    // printf("debug\n");

    // printProcTree(root);

    return root;
}

void printProcTree(TreeNode *root) {
    TreeNode *n = root;
    printTreeNode(root->child);
}

void printTreeNode(TreeNode *n) {
    ProcInfo* p = n->info;
    for(int i = 0 ; i < n->generation; i++) printf("---");
    printf("%5d %-20s: %d %lu %lu\n", p->pid, p->name, p->ppid, p->virt, p->rss);
    if (n->child) {
        printTreeNode(n->child);
    }
    if (n->next) {
        printTreeNode(n->next);
    }
    return;
}

// use hash to find the specified ProcInfo
ProcInfo * findProc(pid_t pid){
    // TODO Level 1-2
    return NULL;
    // END of your code
}

void destoryProcLink(ProcInfo * head) {
    ProcInfo *iter = head;
    ProcInfo *ToDelete = NULL;
    while(iter != NULL) {
        ToDelete = iter;
        free(ToDelete);
        ToDelete = NULL;
        iter = iter->next;
    }
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

int is_pid_folder(const struct dirent *entry) {
    const char *p;
 
    for (p = entry->d_name; *p; p++) {
        if (!isdigit(*p)){
            return 0;
        
        }
    }

    return 1;
}

#define listProcInfo_Bro(info) do{}while(0)
#define listProcInfo_All(info) do{}while(0)
#define _listProcInfo_(scope) listProcInfo_##scope
#define listProcInfo_(scope, info) _listProcInfo_(scope)(info)

void sortProcInfo(ProcInfo * info){
}