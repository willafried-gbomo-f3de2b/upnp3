cmake_minimum_required(VERSION 3.0)

project(upnp3)

# --- deps ---
if (BUILD_DEPS OR PREPARE_DEPS OR UPDATE_DEPS)
    add_subdirectory(thirdparty)
    unset(PREPARE_DEPS CACHE)
    unset(UPDATE_DEPS CACHE)
    unset(BUILD_DEPS CACHE)
endif()


# ---project ---
add_executable(upnp3 
    main1.cpp
    net.cpp
    )   

target_include_directories(upnp3 
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/out/include
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/out/include/pthread
    )

target_compile_features(upnp3 PUBLIC cxx_std_17)

target_compile_definitions(upnp3 PUBLIC UPNP_USE_MSVCPP)

target_link_directories(upnp3
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/out/lib
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/out/bin
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

  

