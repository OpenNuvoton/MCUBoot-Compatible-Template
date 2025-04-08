macro(target_add_scatter_file target sct)
    target_link_options(${target}
        PRIVATE
        --scatter=$<TARGET_OBJECTS:${target}_scatter>
    )

    add_library(${target}_scatter OBJECT)

    target_sources(${target}_scatter
        PRIVATE
            ${sct}
    )

    set_source_files_properties(${sct} PROPERTIES LANGUAGE C)

    add_dependencies(${target}
        ${target}_scatter
    )

    set_target_properties(${target} PROPERTIES LINK_DEPENDS $<TARGET_OBJECTS:${target}_scatter>)

    target_link_libraries(${target}_scatter
        platform_region_defs
    )

    target_compile_options(${target}_scatter
        PRIVATE
            -E
            -xc
    )

endmacro()