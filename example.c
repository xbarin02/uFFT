#include <stddef.h>
#include <complex.h>
#include "ufft.h"
#include <stdio.h>

int main()
{
	size_t N = 1<<3;

	float complex vector[N];

	for(size_t n = 0; n < N; n++) {
		vector[n] = n;
	}

	fft(vector, N);

	printf("DFT:\n");

	for(size_t n = 0; n < N; n++) {
		printf("%f%+fi\n", creal(vector[n]), cimag(vector[n]));
	}

	return 0;
}
