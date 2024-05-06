#include "types.h"
#include "user.h"

void cpu_bound()
{
    int fib1 = 1;
    int fib2 = 1;
    for (int i = 0; i < 10000000; i++)
    {
        fib1 = fib1 + fib2;
        fib2 = fib1 + fib2;
    }
    sleep(10);
}

void io_bound()
{
    for (int j = 0; j < 10; j ++){
    for (int i = 0; i < 100; i++);
    sleep(10);
    for(int k = 0; k < 1000; k++);
    }
}
int main()
{
    int total_childs = 0;
    int ncpu_bounds = 4;
    int nio_bounds = 3;
    printf(1, "Scheduler test starting...\n");
    printf(1, "Creating %d cpu bound processes\n", ncpu_bounds);
    for (int i = 0; i < ncpu_bounds; ++i)
    {
        total_childs++;
        int pid = fork();
        if (pid == 0)
        {
            cpu_bound();
            exit();
        }
    }
    printf(1, "Creating %d io bound processes\n", nio_bounds);
    for (int i = 0; i < nio_bounds; ++i)
    {
        total_childs++;
        int pid = fork();
        if (pid == 0)
        {
            io_bound();
            exit();
        }
    }
    for (int i = 0; i < total_childs; ++i)
    {
        wait();
    }
    printf(1, "Scheduler test completed.\n");

    exit();
}
