#include <stdlib.h>
#include <string.h>

#include <fftw3.h>
#include "dft.h"

struct rdft {
    float* r_in;
    uint32_t r_in_sz;
    fftwf_complex* c_out;
    uint32_t c_out_sz;
    fftwf_plan plan;
    uint32_t n;
};

struct irdft {
    fftwf_complex* c_in;
    uint32_t c_in_sz;
    float* r_out;
    uint32_t r_out_sz;
    fftwf_plan plan;
    uint32_t n;
};

rdft* rdft_create(uint32_t n) {

    uint32_t r_in_sz = n;
    uint32_t c_out_sz = n / 2 + 1;

    float* r_in;
    if ((r_in = fftwf_alloc_real(r_in_sz)) == NULL) {
        return NULL;  // LCOV_EXCL_LINE
    }

    fftwf_complex* c_out;
    if ((c_out = fftwf_alloc_complex(c_out_sz)) == NULL) {
        fftwf_free(r_in);  // LCOV_EXCL_LINE
        return NULL;       // LCOV_EXCL_LINE
    }

    fftwf_plan plan = fftwf_plan_dft_r2c_1d(n, r_in, c_out, FFTW_ESTIMATE);

    rdft* obj = (rdft*) malloc(sizeof(rdft));
    if (obj == NULL) {
        // LCOV_EXCL_START
        fftwf_free(r_in);
        fftwf_free(c_out);
        return NULL;
        // LCOV_EXCL_STOP
    }

    obj->n = n;
    obj->r_in = r_in;
    obj->r_in_sz = r_in_sz;
    obj->c_out = c_out;
    obj->c_out_sz = c_out_sz;
    obj->plan = plan;

    return obj;
}

void rdft_execute(rdft* self, dft_complex* out, float* in) {

    memset(self->r_in, 0, sizeof(float) * self->r_in_sz);

    for (uint32_t i = 0; i < self->r_in_sz; i++)
        self->r_in[i] = in[i];

    fftwf_execute(self->plan);

    // copy out -- normalize by 1 / n
    for (uint32_t i = 0; i < self->c_out_sz; i++) {
        out[i][0] = self->c_out[i][0] / self->n;
        out[i][1] = self->c_out[i][1] / self->n;
    }
}

void rdft_destroy(rdft* self) {
    fftwf_destroy_plan(self->plan);

    if (self->r_in)
        fftwf_free(self->r_in);
    if (self->c_out)
        fftwf_free(self->c_out);
    free(self);
}

irdft* irdft_create(uint32_t n) {
    uint32_t r_out_sz = n;
    uint32_t c_in_sz = n / 2 + 1;

    float* r_out;
    if ((r_out = fftwf_alloc_real(n)) == NULL) {
        return NULL;  // LCOV_EXCL_LINE
    }

    fftwf_complex* c_in;
    if ((c_in = fftwf_alloc_complex(c_in_sz)) == NULL) {
        fftwf_free(r_out);  // LCOV_EXCL_LINE
        return NULL;        // LCOV_EXCL_LINE
    }

    fftwf_plan plan = fftwf_plan_dft_c2r_1d(n, c_in, r_out, FFTW_ESTIMATE);

    irdft* obj = (irdft*) malloc(sizeof(irdft));
    if (obj == NULL) {
        // LCOV_EXCL_START
        fftwf_free(r_out);
        fftwf_free(c_in);
        return NULL;
        // LCOV_EXCL_STOP
    }

    obj->n = n;
    obj->r_out = r_out;
    obj->c_in = c_in;
    obj->c_in_sz = c_in_sz;
    obj->r_out_sz = r_out_sz;
    obj->plan = plan;

    return obj;
}

void irdft_execute(irdft* self, float* out, dft_complex* in) {
    // safety net in case we get fewer bins
    memset(self->c_in, 0, self->c_in_sz * sizeof(fftwf_complex));

    for (uint32_t i = 0; i < self->c_in_sz; i++) {
        self->c_in[i][0] = in[i][0];
        self->c_in[i][1] = in[i][1];
    }

    fftwf_execute(self->plan);

    for (uint32_t i = 0; i < self->r_out_sz; i++) {
        out[i] = self->r_out[i];
    }
}

void irdft_destroy(irdft* self) {

    fftwf_destroy_plan(self->plan);
    if (self->c_in)
        fftwf_free(self->c_in);
    if (self->r_out)
        fftwf_free(self->r_out);
    free(self);
}
