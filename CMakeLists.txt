cmake_minimum_required(VERSION 3.0)


project(upnp3)


# --- deps ---
if (BUILD_DEPS OR PREPARE_DEPS OR UPDATE_DEPS)
    set(BUILD_TYPE "Debug")
    set(OUT_LIB_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/out/lib")
    set(OUT_BIN_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/out/bin")
    set(OUT_INC_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/out/include")
    add_subdirectory(thirdparty)
    unset(PREPARE_DEPS CACHE)
    unset(UPDATE_DEPS CACHE)

    set(BUILD_TYPE "RelWithDebInfo")
    set(OUT_LIB_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/outrd/lib")
    set(OUT_BIN_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/outrd/bin")
    set(OUT_INC_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/outrd/include")
    add_subdirectory(thirdparty)
    unset(BUILD_DEPS CACHE)

endif()


# ---project ---
add_executable(upnp3 
    main1.cpp
    net.cpp
    )   

get_property(OUT TARGET upnp3 PROPERTY BUILD_TYPE)
message("gpt.BUILD_TYPE: ${OUT}")
get_property(OUT TARGET upnp3 PROPERTY CMAKE_BUILD_TYPE)
message("gpt.CMAKE_BUILD_TYPE: ${OUT}")

target_include_directories(upnp3 
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/out/include
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/out/include/pthread
    )

target_compile_features(upnp3 PUBLIC cxx_std_17)

target_compile_definitions(upnp3 PUBLIC UPNP_USE_MSVCPP)


target_link_directories(upnp3
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/out/lib
    )

target_link_libraries(upnp3 
    #upnp_shared
    libupnpd
    #ixml_shared
    ixmld
    matroska
    flac
    sqlite

    Iphlpapi.lib
    )


