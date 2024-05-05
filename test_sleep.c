#include "types.h"
#include "user.h"

int main()
{
    int pid = fork();
    if (pid == 0){
        int c = 0;
        c = 2;
        for (int i = 0; i < 1000000; i++){
            c = c + 2;
        }
        printf(1, "hello\n");
        sleep(1000);
        printf(1, "world\n");
        sleep(300);
        printf(1, "goodbye\n");
        exit();
    }
    else{
        wait();
    }
    exit();
}