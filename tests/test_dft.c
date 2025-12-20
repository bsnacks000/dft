#include "test_dft.h"
#include "../dft.h"

#define FFT_SZ 64

MunitResult test_rdft(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  rdft *dft = rdft_create(FFT_SZ);

  munit_assert_not_null(dft);

  float in[FFT_SZ] = {0};
  in[0] = 1.0;

  int out_sz = FFT_SZ / 2 + 1;

  dft_complex out[out_sz];

  rdft_execute(dft, out, in);

  // all should be 1/FFT_SZ + j0
  for (int i = 0; i < out_sz; i++) {
    // printf("(%.7f, %.7f)\n", out[i][0], out[i][1]);
    munit_assert_double_equal(out[i][0], 1.0 / FFT_SZ, 7);
    munit_assert_double_equal(out[i][0], 0.0, 1);
  }

  rdft_destroy(dft);

  return MUNIT_OK;
}

MunitResult test_irdft(const MunitParameter params[], void *data) {
  (void)params;
  (void)data;

  irdft *idft = irdft_create(FFT_SZ);
  munit_assert_not_null(idft);

  int in_sz = FFT_SZ / 2 + 1;
  dft_complex in[in_sz];

  for (int i = 0; i < in_sz; i++) {
    in[i][0] = 1.0 / FFT_SZ;
    in[i][1] = 0.0;
  }

  float out[FFT_SZ] = {0};

  irdft_execute(idft, out, in);

  for (int i = 0; i < FFT_SZ; i++) {
    if (i == 0)
      munit_assert_double_equal(out[i], 1.0, 1);
    else
      munit_assert_double_equal(out[i], 0.0, 1);
  }

  return MUNIT_OK;
}
