#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

int main() {

    int pid, n;
    enum proctype t;

    n = 5;

    printf(1, "Starting scheduler test one...\n");
    printf(1, "Creating %d processes\n", n);

    for (int i = 0; i < n; i++) {
        t = (i < 5) ? BATCH : INTERACTIVE;
        char *type = (t == INTERACTIVE) ? "INTERACTIVE" : "BATCH";
        pid = fork();
        setproctype(getpid(), t);  
        if (pid == 0) { 
            printf(1, "\nProcess %d of type %s started\n", getpid(), type);

            for (int j = 0; j < 10000000; j++) {
                asm("nop"); 
            }

            printf(1, "\nProcess %d of type %s finished\n", getpid(), type);
            exit();
        }
    }

    for (int i = 0; i < n; i++) { // wait for children
        wait();
    }

    printf(1, "Scheduler test completed.\n");

    exit();
}
