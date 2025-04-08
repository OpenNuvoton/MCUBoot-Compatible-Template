add_library(platformlib STATIC)
add_library(platform_common_interface INTERFACE)
add_library(platform_region_defs INTERFACE)

add_subdirectory(${PLATFORM_NAME})

target_include_directories(platform_common_interface
    INTERFACE
        include
)

target_link_libraries(platformlib
    PUBLIC
        platform_common_interface
        bsp
)

target_compile_definitions(platformlib
    INTERFACE
        PLATFORM_NAME=${PLATFORM_NAME}
        SLOT_NUM=${SLOT_NUM}
)
