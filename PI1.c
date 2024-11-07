#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 1000000000;
double step;

int main(int argc, char* argv[])
{
	clock_t spstart, spstop;
	double sswtime, sewtime;
	//volatile
	double x, pi, sum = 0.0;
	int i;
	//SEKWENCYJNIE
	sswtime = omp_get_wtime();
	spstart = clock();

	step = 1. / (double)num_steps;

	for (i = 0; i < num_steps; i++)
	{
		x = (i + .5) * step;
		sum = sum + 4.0 / (1. + x * x);
	}

	pi = sum * step;
	spstop = clock();
	sewtime = omp_get_wtime();
	
	printf("%15.12f artosc liczby PI sekwencyjnie \n", pi);
	printf("Czas procesorów przetwarzania sekwencyjnego  %f sekund \n", ((double)(spstop - spstart) / CLOCKS_PER_SEC));
	printf("Czas trwania obliczen sekwencyjnych - wallclock %f sekund \n", sewtime - sswtime);

	return 0;
}
