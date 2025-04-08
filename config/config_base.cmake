set(PLATFORM_NAME                       "m480" CACHE STRING "Platform to build app for")
set(SLOT_NAME                           "a" CACHE STRING "Choose the image slot [a, b]")
set(EXE_NAME                            bl3_${SLOT_NAME} CACHE STRING "The name of the execution file")
set(HEADER_SIZE                         0x400 CACHE STRING "Header size")
set(PRIMARY_SLOT_OFFST                  0x20000 CACHE STRING "The primary image slot offset relative to its flash device's storage")
set(SECONDARY_SLOT_OFFST                0x60000 CACHE STRING "The secondary image slot offset relative to its flash device's storage")
set(UPGRADE_STRATEGY                    "OVERWRITE_ONLY" CACHE STRING "Upgrade strategy for images")
set(RAM_LOAD_ADDR                       0x2000A000 CACHE STRING "The load address where the image is copied")
set(MCUBOOT_SIG_TYPE                    "RSA" CACHE STRING "Algorithm to use for signature validation")
set(MCUBOOT_SIG_LEN                     "3072" CACHE STRING "Algorithm to use for signature validation")
set(USE_IMAGE_SIGNING                   OFF CACHE BOOL "Enable post-build signing of the firmware image")
set(MCUBOOT_GENERATE_SIGNING_KEYPAIR    OFF CACHE BOOL "Generate new keypair for signing and use that instead of MCUBOOT_KEY")
set(MCUBOOT_KEY                         "${CMAKE_SOURCE_DIR}/root-${MCUBOOT_SIG_TYPE}-${MCUBOOT_SIG_LEN}.pem" CACHE FILEPATH "Path to key with which to sign binary")
set(MCUBOOT_IMAGE_VERSION               "1.0" CACHE STRING "Version number of the image")
set(MCUBOOT_ALIGN_VAL                   16 CACHE STRING "align option for mcuboot and build image with imgtool [1, 2, 4, 8, 16, 32]")
set(BL2_HEADER_SIZE                     0x400 CACHE STRING "Header size")
set(IMAGE_SLOT_SIZE                     0x8000 CACHE STRING "Image slot size")

# Specifying a scope of the accepted values of UPGRADE_STRATEGY for
# platforms to choose a specific upgrade strategy for images. These certain
# configurations will be used to facilitate the later validation.
set_property(CACHE UPGRADE_STRATEGY PROPERTY STRINGS "OVERWRITE_ONLY;SWAP_USING_SCRATCH;SWAP_USING_MOVE;DIRECT_XIP;RAM_LOAD")