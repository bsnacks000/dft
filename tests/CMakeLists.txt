set(UNIT_TEST_NAME unit_tests)
file(GLOB SRC_FILES *.c)

add_executable(${UNIT_TEST_NAME}
    ${SRC_FILES}
)


target_link_libraries(${UNIT_TEST_NAME} PRIVATE ${PROJECT_NAME} m  PkgConfig::FFTW3F)
target_compile_options(${UNIT_TEST_NAME} PRIVATE
    -Wextra -Wall -Wpedantic -Werror
)

# coverage options are compiler specific
if(COVERAGE)
    if(CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang|AppleClang)$")
        target_compile_options(${UNIT_TEST_NAME} PRIVATE -O0 -g --coverage)
        target_link_options(${UNIT_TEST_NAME} PRIVATE --coverage)
    else()
        message(FATAL_ERROR "Coverage not supported with this compiler: ${CMAKE_C_COMPILER_ID}")
    endif()
endif()
