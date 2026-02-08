#ifndef DFT_H
#define DFT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef struct rdft rdft;
typedef struct irdft irdft;

typedef float dft_complex[2];

/**
 * @brief create an rdft object of size n real numbers and size n/2 + 1 complex.
 */
rdft* rdft_create(uint32_t n);

/**
 * @brief execute the forward dft. The complex result will be scaled by 1/N.
 */
void rdft_execute(rdft* self, dft_complex* out, float* in);

/**
 * @brief create an rdft object.
 */
void rdft_destroy(rdft* self);

/**
 * @brief create an irdft object of size n real numbers and size n/2 + 1
 * complex.
 */
irdft* irdft_create(uint32_t n);

/**
 * @brief execute the inverse dft. Does not scale the dft output.
 */
void irdft_execute(irdft* self, float* out, dft_complex* in);

/**
 * @brief destroy an irdft object.
 */
void irdft_destroy(irdft* self);

#ifdef __cplusplus
}
#endif

#endif
