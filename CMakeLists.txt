cmake_minimum_required(VERSION 3.26)

set(PROJECT_NAME dft)
project(${PROJECT_NAME} LANGUAGES C VERSION 0.1.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set default build type if not set
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

# Export compile commands for tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Enable position independent code for libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (APPLE)
    message("Building on Apple.")
    add_compile_definitions(-DMACOS=1)
endif()

find_package(PkgConfig REQUIRED)

#pkg_check_modules(FFTW3 REQUIRED fftw3f)
pkg_check_modules(FFTW3F REQUIRED IMPORTED_TARGET fftw3f)


# always build the main static library
file(GLOB SRC_FILES ./*.c)


# note the build tree includes the generated headers
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_SOURCE_DIR}"
)
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::FFTW3F)

target_compile_options(${PROJECT_NAME} PRIVATE -Wextra -Wall -Wpedantic -Werror
        -Wmissing-declarations -Wmissing-prototypes
)

if(COVERAGE)
    message(STATUS "Building with coverage instrumentation")
    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE -fprofile-instr-generate -fcoverage-mapping)
        target_link_options(${PROJECT_NAME} PRIVATE -fprofile-instr-generate -fcoverage-mapping)
    elseif(CMAKE_C_COMPILER_ID MATCHES "GNU")
        target_compile_options(${PROJECT_NAME} PRIVATE --coverage -O0 -g)
        target_link_options(${PROJECT_NAME} PRIVATE --coverage)
    else()
        message(FATAL_ERROR "Coverage not supported with this compiler")
    endif()
endif()

# build the tests
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
