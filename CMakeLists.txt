cmake_minimum_required(VERSION 3.22)

include(${CMAKE_SOURCE_DIR}/config/config_base.cmake)
include(${CMAKE_SOURCE_DIR}/toolchain/scatter.cmake)

project(App VERSION 1.0
            LANGUAGES C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

set(BIN_DIR ${PROJECT_BINARY_DIR}/bin)

set(ALLOWED_SLOT_NAME a b)
list(FIND ALLOWED_SLOT_NAME ${SLOT_NAME} SLOT_NUM)

add_subdirectory(src)
add_subdirectory(platform)