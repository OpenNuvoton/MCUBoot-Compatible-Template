add_library(bsp STATIC)

#========================= platformlib ========================================#

target_sources(platformlib
    PRIVATE
        platform.c
)

#========================= bsp ================================================#

target_include_directories(bsp
    PUBLIC
        bsp/Library/StdDriver/inc
        bsp/Library/Device/Nuvoton/M480/Include
        bsp/Library/CMSIS/Include
)

target_sources(bsp
    PRIVATE
        bsp/Library/Device/Nuvoton/M480/Source/ARM/startup_M480.s
        bsp/Library/Device/Nuvoton/M480/Source/system_M480.c
        bsp/Library/StdDriver/src/retarget.c
        bsp/Library/StdDriver/src/uart.c
        bsp/Library/StdDriver/src/clk.c
        bsp/Library/StdDriver/src/sys.c
)

target_compile_definitions(bsp
    PUBLIC
        __MICROLIB
)

#========================= Platform region defs ===============================#
target_include_directories(platform_region_defs
    INTERFACE
        partition
)

if(UPGRADE_STRATEGY STREQUAL "RAM_LOAD")
    math(EXPR IMAGE_OFFSET "${RAM_LOAD_ADDR} + ${HEADER_SIZE}" OUTPUT_FORMAT HEXADECIMAL)
elseif(UPGRADE_STRATEGY STREQUAL "DIRECT_XIP")
    if(SLOT_NUM EQUAL 0)
        math(EXPR IMAGE_OFFSET "${PRIMARY_SLOT_OFFST} + ${HEADER_SIZE}" OUTPUT_FORMAT HEXADECIMAL)
    elseif(SLOT_NUM EQUAL 1)
        math(EXPR IMAGE_OFFSET "${SECONDARY_SLOT_OFFST} + ${HEADER_SIZE}" OUTPUT_FORMAT HEXADECIMAL)
    else()
        message(FATAL_ERROR "Unknown slot number")
    endif()
else()
    math(EXPR IMAGE_OFFSET "${PRIMARY_SLOT_OFFST} + ${HEADER_SIZE}" OUTPUT_FORMAT HEXADECIMAL)
endif()

message(IMAGE_OFFSET=${IMAGE_OFFSET})

target_compile_definitions(platform_region_defs
    INTERFACE
        IMAGE_OFFSET=${IMAGE_OFFSET}
)

#========================= Platform common defs ===============================#

target_add_scatter_file(${EXE_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/scatter/${PLATFORM_NAME}.sct
)
