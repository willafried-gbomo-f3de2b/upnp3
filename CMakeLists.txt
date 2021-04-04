cmake_minimum_required(VERSION 3.0)


project(upnp3)


# --- deps ---
if (BUILD_DEPS OR PREPARE_DEPS OR UPDATE_DEPS)

    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/thirdparty)

    set(BUILD_TYPE "Debug")
    # set(OUT_LIB_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/out/lib")
    # set(OUT_BIN_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/out/bin")
    # set(OUT_INC_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/out/include")
    # add_subdirectory(thirdparty)
# message("  --- deps ---")
# execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty -D BUILD_TYPE=${BUILD_TYPE} -D BUILD_DEPS="${BUILD_DEPS}" -D OUT_LIB_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/deps/lib -D OUT_BIN_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/deps/bin -D OUT_INC_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/deps/include
# 	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/thirdparty
# 	# OUTPUT_QUIET
# 	)

    set(BUILD_TYPE "Release")
    execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty -D BUILD_TYPE=${BUILD_TYPE} -D BUILD_DEPS="${BUILD_DEPS}" -D OUT_LIB_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/deps-rd/lib -D OUT_BIN_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/deps-rd/bin -D OUT_INC_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/deps-rd/include
	WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/thirdparty
	# OUTPUT_QUIET
	)

    unset(PREPARE_DEPS CACHE)
    unset(UPDATE_DEPS CACHE)
    unset(BUILD_DEPS CACHE)

    unset(BUILD_TYPE)

    # set(BUILD_TYPE "RelWithDebInfo")
    # set(OUT_LIB_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/outrd/lib")
    # set(OUT_BIN_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/outrd/bin")
    # set(OUT_INC_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/outrd/include")
    # add_subdirectory(thirdparty)
    # unset(BUILD_DEPS CACHE)

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
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/deps/include
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/deps/include/pthread
    )

target_compile_features(upnp3 PRIVATE cxx_std_17)

target_compile_definitions(upnp3 PRIVATE UPNP_USE_MSVCPP)


target_link_directories(upnp3
    PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/deps/lib
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


