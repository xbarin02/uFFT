#ifndef IFT_H
#define IFT_H

#include <complex.h>
#include <stddef.h>

/**
 * @brief FFT algorithm (inverse transform)
 *
 * This function computes inverse radix-2 fast Fourier transform (FFT).
 * The output is written in-place over the input.
 *
 * @param vector An array of @p N complex values in single-precision floating-point format.
 * @param N The size of the transform must be a power of two.
 *
 * @return Zero for success.
 */
int ift(float complex *vector, size_t N);

#endif
