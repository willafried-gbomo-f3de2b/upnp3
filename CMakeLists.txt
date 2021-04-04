cmake_minimum_required(VERSION 3.0)


project(upnp3)


# --- deps clean ---
if(CLEAN_DEPS)
    message("cleaning deps: ${CMAKE_CURRENT_BINARY_DIR}, thridparty, deps")
    file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/thirdparty)
    file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/deps)
    unset(CLEAN_DEPS CACHE)
endif()


# --- deps build ---
if (BUILD_DEPS OR PREPARE_DEPS OR UPDATE_DEPS)

    message("--- deps: ${BUILD_TYPE} ---")
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/thirdparty)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/deps/${BUILD_TYPE})

    # set(OUT_LIB_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/out/lib")
    # set(OUT_BIN_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/out/bin")
    # set(OUT_INC_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/out/include")
    # add_subdirectory(thirdparty)

    message("  -- PREPARE_DEPS=${PREPARE_DEPS}, UPDATE_DEPS=${UPDATE_DEPS}, BUILD_DEPS=${BUILD_DEPS} --")
    execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty -D BUILD_TYPE=${BUILD_TYPE} -D BUILD_DEPS="${BUILD_DEPS}" -D PREPARE_DEPS="${PREPARE_DEPS}" -D UPDATE_DEPS="${UPDATE_DEPS}" -D OUT_LIB_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/deps/${BUILD_TYPE}/lib -D OUT_BIN_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/deps/${BUILD_TYPE}/bin -D OUT_INC_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/deps/${BUILD_TYPE}/include
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/thirdparty
        # OUTPUT_QUIET
        )
    
    unset(PREPARE_DEPS CACHE)
    unset(UPDATE_DEPS CACHE)

    unset(BUILD_DEPS CACHE)
    #unset(BUILD_TYPE CACHE)

endif()


# ---project ---
add_executable(upnp3 
    main1.cpp
    net.cpp
    )

target_include_directories(upnp3 
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/${BUILD_TYPE}/include
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/${BUILD_TYPE}/include/pthread
    )

target_compile_features(upnp3 PRIVATE cxx_std_17)

target_compile_definitions(upnp3 PRIVATE UPNP_USE_MSVCPP)

target_link_directories(upnp3
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/deps/${BUILD_TYPE}/lib
    )

target_link_libraries(upnp3 
    # deps ---
    #upnp_shared
    libupnpd
    #ixml_shared
    ixmld
    matroska
    flac
    sqlite
    # windows ---
    Iphlpapi.lib
    )


