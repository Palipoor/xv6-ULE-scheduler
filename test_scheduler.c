#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"

void cpu_bound() {
    int fib1 = 1;
    int fib2 = 1;
    for (int i = 0; i < 10000000; i++) {
        fib1 = fib1 + fib2;
        fib2 = fib1 + fib2;
    }
}

void io_bound() {
    int p[2];
    if (pipe(p) == -1) {
        printf(1, "pipe failed\n");
        exit();
    }
    int pid = fork();
    if(pid == 0) {
        close(p[0]);
        for (int i = 0; i < 128; i++){
        write(p[1], "ABCD", 4);
        for (int j = 0; j < 10000000; j++) 
            asm("nop");
        }
        close(p[1]);
     } else {
        close(p[1]);
        char buf[512];
        int n;
        n = read(p[0], buf, sizeof buf);
        while (n > 0) {
            n = read(p[0], buf, sizeof buf);
        }
        close(p[0]);
        wait(); 
}
}
int main() {

    printf(1, "Scheduler test starting...\n");
    int pid = fork();
    if (pid == 0){
        printf(1, "Creating %d cpu bound processes\n", 3);
        for (int i = 0; i < 3; i++) {
            int pid = fork();
            if (pid == 0) {
                cpu_bound();
                exit();
            }else
                wait();
        }
        printf(1, "Creating %d io bound processes in total\n", 4);
        for (int i = 0; i < 2; i++) {
            int pid = fork();
            if (pid == 0) {
                io_bound();
                exit();
            }
            else
                wait();
        }
    }
    wait();
    printf(1, "Scheduler test completed.\n");

    exit();
}
