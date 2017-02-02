#include "ift.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

static int ctz(size_t N)
{
	int ctz1 = 0;

	while( N ) {
		ctz1++;
		N >>= 1;
	}

	return ctz1-1;
}

static void nop_split(const float complex *x, float complex *X, size_t N)
{
	for(size_t n = 0; n < N/2; n++) {
		X[0/2+n] = x[2*n+0];
		X[N/2+n] = x[2*n+1];
	}
}

static void fft_split(const float complex *x, float complex *X, size_t N, float complex phi)
{
	for(size_t n = 0; n < N/2; n++) {
		X[0/2+n] = (x[2*n+0] + x[2*n+1] * cexp(+2*(float)M_PI*I*phi))/2;
		X[N/2+n] = (x[2*n+0] - x[2*n+1] * cexp(+2*(float)M_PI*I*phi))/2;
	}
}

static size_t revbits(size_t v, int J)
{
	size_t r = 0;

	for(int j = 0; j < J; j++) {
		r |= ( (v>>j)&1 ) << (J-1-j);
	}

	return r;
}

static int nop_reverse(int b, float complex *buffers[2], size_t N)
{
	int J = ctz(N);

	for(int j = 0; j < J-1; j++, b++) {
		size_t delta = N>>j;

		for(size_t n = 0; n < N; n += delta) {
			nop_split(buffers[b&1]+n, buffers[~b&1]+n, delta);
		}
	}

	return b;
}

static int fft_reverse(int b, float complex *buffers[2], size_t N)
{
	int J = ctz(N);

	for(int j = 0; j < J; j++, b++) {
		size_t delta = N>>j;

		for(size_t n = 0; n < N; n += delta) {
			float complex phi = (float)revbits( n/delta, j) / (float)(2<<j);
			fft_split(buffers[b&1]+n, buffers[~b&1]+n, delta, phi);
		}
	}

	return b;
}

int ift(float complex *vector, size_t N)
{
	if( !N ) return 0;

	if( N & (N-1) ) return 1;

	float complex *buffers[2] = { vector, malloc(N*sizeof(float complex)) };

	if( !buffers[1] ) return -1;

	int b = 0;

	b = nop_reverse(b, buffers, N);
	b = fft_reverse(b, buffers, N);
	b = nop_reverse(b, buffers, N);

	memmove(vector, buffers[b&1], N*sizeof(float complex));

	free( buffers[1] );

	return 0;
}
