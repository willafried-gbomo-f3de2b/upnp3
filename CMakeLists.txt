cmake_minimum_required(VERSION 3.0)

project(upnp2)


add_subdirectory(thirdparty)


add_executable(upnp2 
    main1.cpp
    net.cpp
    )   

target_compile_features(upnp2 PUBLIC cxx_std_17)

target_link_libraries(upnp2 
    upnp_shared
    ixml_shared

    Iphlpapi.lib
    )

  

