add_executable(${EXE_NAME})

target_sources(${EXE_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)

target_link_libraries(${EXE_NAME}
    PRIVATE
        platformlib
)

target_link_options(${EXE_NAME}
    PRIVATE
        --library_type=microlib
        --symbols
        --map
)

add_custom_target(${EXE_NAME}_bin
    SOURCES ${BIN_DIR}/${EXE_NAME}.bin
)

add_custom_command(
    OUTPUT ${BIN_DIR}/${EXE_NAME}.bin
    DEPENDS ${EXE_NAME}
    COMMAND ${ARM_ELF2BIN}
        --bin $<TARGET_FILE:${EXE_NAME}>
        --output ${BIN_DIR}/${EXE_NAME}.bin
)

add_custom_target(${EXE_NAME}_binaries
    ALL
    DEPENDS ${EXE_NAME}_bin
)

############################### IMAGE SIGNING ##################################

if(USE_IMAGE_SIGNING)
    find_package(Python3 COMPONENTS Interpreter)

    execute_process(
        COMMAND ${Python3_EXECUTABLE} -c "import imgtool"
        RESULT_VARIABLE _import_result
    )

    if(NOT _import_result EQUAL 0)
        message(FATAL_ERROR "Python module 'imgtool' not found!")
    endif()

    if(MCUBOOT_GENERATE_SIGNING_KEYPAIR)
        if(NOT MCUBOOT_SIG_TYPE STREQUAL "RSA")
            message(FATAL_ERROR "We only support RSA key generation right now.")
        endif()
        add_custom_target(generated_private_key
            SOURCES
                generated_private_key.pem
        )
        add_custom_command(OUTPUT generated_private_key.pem
            COMMAND ${Python3_EXECUTABLE} -m imgtool.main
                keygen
                -k generated_private_key.pem
                -t rsa-${MCUBOOT_SIG_LEN}
            COMMAND ${CMAKE_COMMAND} -E copy generated_private_key.pem $<TARGET_FILE_DIR:${EXE_NAME}>
        )
        set(MCUBOOT_KEY $<TARGET_FILE_DIR:${EXE_NAME}>/generated_private_key.pem CACHE FILEPATH "" FORCE)
    endif()


    add_custom_target(public_key ALL
        SOURCES
            image_signing_public_key.pem
    )

    add_custom_command(OUTPUT image_signing_public_key.pem
        # If MCUBOOT_GENERATE_SIGNING_KEYPAIR=ON then the command should depend on that
        # to make sure that the key is generated and copied to the MCUBOOT_KEY path.
        DEPENDS $<IF:$<BOOL:${MCUBOOT_GENERATE_SIGNING_KEYPAIR}>,generated_private_key,>
        COMMAND ${Python3_EXECUTABLE} -m imgtool.main
            getpub
            -k ${MCUBOOT_KEY}
            -e pem
            -o image_signing_public_key.pem
        COMMAND ${CMAKE_COMMAND} -E copy image_signing_public_key.pem ${BIN_DIR}/image_signing_public_key.pem
    )

    add_custom_target(signed_bin
        SOURCES ${EXE_NAME}_signed.bin
    )

    add_custom_command(OUTPUT ${EXE_NAME}_signed.bin
        DEPENDS ${BIN_DIR}/${EXE_NAME}.bin
        DEPENDS $<IF:$<BOOL:${MCUBOOT_GENERATE_SIGNING_KEYPAIR}>,generated_private_key,>
        COMMAND ${Python3_EXECUTABLE} -m imgtool.main
            sign
            -v ${MCUBOOT_IMAGE_VERSION}
            -k ${MCUBOOT_KEY}
            --align ${MCUBOOT_ALIGN_VAL}
            --pad
            --pad-header
            -H ${BL2_HEADER_SIZE}
            -S ${IMAGE_SLOT_SIZE}
            $<$<STREQUAL:${UPGRADE_STRATEGY},OVERWRITE_ONLY>:--overwrite-only>
            $<$<STREQUAL:${UPGRADE_STRATEGY},RAM_LOAD>:--load-addr=${RAM_LOAD_ADDR}>
            ${BIN_DIR}/${EXE_NAME}.bin
            ${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}_signed.bin
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${EXE_NAME}_signed.bin ${BIN_DIR}
    )

    add_custom_target(signed_images
        ALL
        DEPENDS ${EXE_NAME}_signed.bin
    )
endif()
