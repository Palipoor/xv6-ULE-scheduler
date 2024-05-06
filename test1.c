#include "types.h"
#include "user.h"

int is_prime(int n){
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;
    for (int i = 5; i * i <= n; i = i + 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    }
    return 1;
}

int recursive_func(int n){
    if (n <= 0)
        return 0;
    if (n == 1)
        return 1;
    if (n % 2 == 0)
        return 1 + recursive_func(n - 2);
    return 1 + recursive_func(n - 1);
}
void cpu_bound(int seed)
{
    int x = seed % 4;
    int mil = 1000000;
    int kilo = 1000;
    int hundred = 100;
    switch (x)
    {
    case 0:
        int fib1 = 1;
        int fib2 = 1;
        for (int k = 0; k < mil; k++)
        {
            fib1 = fib1 + fib2;
            fib2 = fib1 + fib2;
        }
        break;
    case 1:
        int z = 0;
        for (int k = hundred; k < mil; k++)
        {
            for (int j = 1; j < hundred; j++){
                z = k % j;
            }
        }
        break;
    case 2:
        for (int k = 1; k < kilo; k++)
        {
            int p = is_prime(k);
            
        }
        break;
    case 3:
        for (int k = 0; k < hundred; k++)
        {
            int r = recursive_func(k);
        }
        break;
    }
    return;
}

int main()
{

    int nprocs = 10;
    printf(1, "Scheduler test 1 starting...\n");
    for (int i = 0; i < nprocs; i++)
    {
        int pid = fork();
        if (pid == 0)
        {
            cpu_bound(i);
            sleep(5);
            exit();
        }
    }
    for (int i = 0; i < nprocs; i++)
    {
        wait();
    }
    printf(1, "Scheduler test 1 completed.\n");

    exit();
}
