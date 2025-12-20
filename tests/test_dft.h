
#ifndef TEST_DFT_H
#define TEST_DFT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "munit.h"

MunitResult test_rdft(const MunitParameter params[], void* data);

MunitResult test_irdft(const MunitParameter params[], void* data);

static MunitTest dft_test_module[] = {
    {"/rdft", test_rdft, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/irdft", test_irdft, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
};

static const MunitSuite dft_test_suite = {
    "/dft",                 /* name */
    dft_test_module,        /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

#ifdef __cplusplus
}
#endif
#
#endif
