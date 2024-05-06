#include "types.h"
#include "user.h"

void cpu_bound()
{
    int fib1 = 1;
    int fib2 = 1;
    for (int i = 0; i < 500000000; i++)
    {
        fib1 = fib1 + fib2;
        fib2 = fib1 + fib2;
    }
}

void io_bound()
{
    for (int j = 0; j < 100; j ++){
        for (int i = 0; i < 100; i++);
        sleep(20);
        for(int k = 0; k < 100; k++);
    }
}
int main()
{
    printf(1, "Scheduler test 3 starting...\n");
    int pid = fork();
    if (pid == 0)
    {
        cpu_bound();
        exit();
    }else{
        pid = fork();
        if (pid == 0)
        {
            io_bound();
            exit();
        }
    }
    wait();
    wait();
    printf(1, "Scheduler test 3 completed.\n");

    exit();
}