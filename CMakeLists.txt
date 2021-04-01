cmake_minimum_required(VERSION 3.0)

message("CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

project(upnp3)


if (BUILD_DEPS)
    add_subdirectory(thirdparty)
else()

endif()


add_executable(upnp3 
    main1.cpp
    net.cpp
    )   

target_include_directories(upnp3 
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/out/include
    )

# target_include_directories(upnp2 
#     PUBLIC thirdparty/pupnp/upnp/inc
#     PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/pupnp/upnp/inc
#     PUBLIC thirdparty/pupnp/ixml/inc
#     )

# target_link_directories(upnp2 
#     PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/pupnp/upnp/Debug
#     PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/pupnp/ixml/Debug
#     )

target_compile_features(upnp3 PUBLIC cxx_std_17)


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

  

