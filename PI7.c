#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 1000000000;
double step;

int main(int argc, char* argv[])
{

    volatile double tab[50] __attribute__((aligned(64)));
    for (int i = 0; i < 50; i++) {
        tab[i] = 0.0;
    }
    clock_t start, stop;
    double pi, sum = 0.0;
    double startwtime, endwtime;
    step = 1.0 / (double)num_steps;
    for (int offset = 0; offset < 50; offset++)
    {
        omp_set_num_threads(2);
        sum = 0.0;

        for (int w = 0; w < 50; w++) {
            tab[w] = 0.0;
        }

        startwtime = omp_get_wtime();
        start = clock();
        
        #pragma omp parallel
        {
            int id = omp_get_thread_num();
            #pragma omp for
            for (int i = 0; i < num_steps; i++)
            {
                double x = (i + 0.5) * step;
                tab[(id + offset) % 50] += 4.0 / (1.0 + x * x);
            }
            
            #pragma omp atomic
            sum += tab[(id + offset) % 50];
        }

        pi = sum * step;
        stop = clock();
        endwtime = omp_get_wtime();

        printf("%d. %f %f %15.12f\n",
               offset, ((double)(stop - start) / CLOCKS_PER_SEC), endwtime - startwtime, pi);
    }

    return 0;
}
