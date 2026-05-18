#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

int numbers[100];
int n;
double mean, median, std_dev;

void *calculate_mean(void *arg)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += numbers[i];
    }

    mean = (double)sum / n;
    pthread_exit(0);
}

void *calculate_median(void *arg)
{
    int temp[100];
    for (int i = 0; i < n; i++)
    {
        temp[i] = numbers[i];
    }

    // sort
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (temp[j] > temp[j + 1])
            {
                int t = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = t;
            }
        }
    }

    if (n % 2 == 0)
    {
        median = (temp[n / 2] + temp[n / 2 - 1]) / 2.0;
    }
    else
    {
        median = temp[n / 2];
    }

    pthread_exit(0);
}

void *calculate_std_dev(void *arg)
{
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        sum += (numbers[i] - mean) * (numbers[i] - mean);
    }

    std_dev = sqrt(sum / n);
    pthread_exit(0);
}

int main(int argc, char *argv[])
{

    pthread_t t1, t2, t3; // create thread ids

    n = argc - 1;
    for (int i = 0; i < n; i++)
    {
        numbers[i] = atoi(argv[i + 1]);
    }

    // create threads
    pthread_create(&t1, NULL, calculate_mean, NULL);
    pthread_join(t1, NULL);

    pthread_create(&t2, NULL, calculate_median, NULL);
    pthread_create(&t3, NULL, calculate_std_dev, NULL);

    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Mean: %.2f\n", mean);
    printf("Median: %.2f\n", median);
    printf("Standard Deviation: %.2f\n", std_dev);

    return 0;
}