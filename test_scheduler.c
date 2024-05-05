#include "types.h"
#include "user.h"

void cpu_bound()
{
    int fib1 = 1;
    int fib2 = 1;
    for (int i = 0; i < 100000000; i++)
    {
        fib1 = fib1 + fib2;
        fib2 = fib1 + fib2;
    }
}

void io_bound()
{
    int p[2];
    if (pipe(p) == -1)
    {
        printf(1, "pipe failed\n");
        exit();
    }
    int pid = fork();
    if (pid == 0)
    {
        close(p[0]);
        for (int i = 0; i < 1024; ++i)
        {
            write(p[1], "A", 1);
            for (int j = 0; j < 100000; j++)
                asm("nop");
        }
        close(p[1]);
    }
    else
    {
        close(p[1]);
        char buf[1024];
        int n;
        n = read(p[0], buf, 1);
        while (n > 0)
        {
            n = read(p[0], buf, 1);
            
        }
        close(p[0]);
        wait();
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
    printf(1, "Creating %d io bound processes\n", 2 * nio_bounds);
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
