#include "munit.h"

#include "test_dft.h"

/// see: https://github.com/nemequ/munit/blob/master/example.c

int main(int argc, char *argv[MUNIT_ARRAY_PARAM(argc + 1)]) {

  // register test_suites
  // sentinel
  MunitSuite all_test_suites[] = {
      dft_test_suite,
      {NULL, NULL, NULL, 1, MUNIT_SUITE_OPTION_NONE},
  };

  MunitSuite test_suite_main = {
      "/spctrl",              /* name */
      NULL,                   /* tests */
      all_test_suites,        /* suites */
      1,                      /* iterations */
      MUNIT_SUITE_OPTION_NONE /* options */
  };

  return munit_suite_main(&test_suite_main, NULL, argc, argv);
}
