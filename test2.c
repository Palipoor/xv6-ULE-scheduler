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
void io_bound(int seed){
    int x = seed % 4;
    int mil = 1000000;
    int kilo = 1000;
    int hundred = 100;
    switch (x)
    {
    case 0:
        for (int k = 0; k < kilo; k++)
        {
            for (int j = 0; j < hundred; j++);
            sleep(10);
        }
        break;
    case 1:
        for (int k = 0; k < kilo; k++)
        {
            sleep(2);
            for (int j = 0; j < 10; j++);
            sleep(2);
            for (int j = 0; j < 10; j++);
            sleep(2);
            for (int j = 0; j < 10; j++);
        }
        break;
    case 2:
        for (int k = 0; k < 10; k++)
        {
            sleep(200);
            for (int j = 0; j < hundred; j++);
            sleep(200);
        }
        break;
    case 3:
        for (int k = 0; k < kilo; k++)
        {
            is_prime(k);
            sleep(10);
        }
        break;
    }
    return;
}
int main()
{
    int nprocs = 10;
    printf(1, "Scheduler test 2 starting...\n");
    for (int i = 0; i < nprocs; i++)
    {
        int pid = fork();
        if (pid == 0)
        {
            io_bound(i);
            exit();
        }
    }
    for (int i = 0; i < nprocs; i++)
    {
        wait();
    }
    printf(1, "Scheduler test 2 completed.\n");

    exit();
}