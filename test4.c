#include "types.h"
#include "user.h"


void long_batch(){
    int c = 0;
    for (int i = 0; i < 200000000; i++){
        c = c + (i % 4);
    }
}

void interactive(t){
    int c = 0;
    for (int i = 0; i < 10; i++){
        sleep(t);
        c = c + (i % 4);
    }
}
int main(){
    int num_interactive = 4;
    printf(1, "Scheduler test 4 starting...\n");
    int pid = fork();
    if (pid == 0){
        long_batch();
        exit();
    }else{
        for (int i = num_interactive + 1; i > 0; i--){
            pid = fork();
            if (pid == 0){
                interactive(i * 50);
                exit();
            }
        }
    }
    for (int i = num_interactive + 1; i > 0; i--){
        wait();
    }
    printf(1, "Scheduler test 4 completed.\n");
    exit();
}