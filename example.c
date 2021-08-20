#include <stddef.h>
#include <complex.h>
#include "fft.h"
#include "ift.h"
#include <stdio.h>

int main()
{
	size_t N = 1 << 3;

	float complex vector[N];

	for (size_t n = 0; n < N; n++) {
		vector[n] = n;
	}

	printf("in time domain:\n");

	for (size_t n = 0; n < N; n++) {
		printf("%f%+fi\n", creal(vector[n]), cimag(vector[n]));
	}

	fft(vector, N);

	printf("in frequency domain:\n");

	for (size_t n = 0; n < N; n++) {
		printf("%f%+fi\n", creal(vector[n]), cimag(vector[n]));
	}

	ift(vector, N);

	printf("in time domain:\n");

	for (size_t n = 0; n < N; n++) {
		printf("%f%+fi\n", creal(vector[n]), cimag(vector[n]));
	}

	return 0;
}
