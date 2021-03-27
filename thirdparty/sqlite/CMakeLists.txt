

# pthreads4w
# option (BUILD_TESTING "" OFF)
# set(BUILD_TESTING OFF CACHE BOOL "")
# add_subdirectory(pthreads4w)

# install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pthreads4w/PTHREADS4WConfig.cmake"
#               "${CMAKE_CURRENT_BINARY_DIR}/pthreads4w/PTHREADS4WConfigVersion.cmake"
#         DESTINATION out
#         )


# pthreads4w
message("--- pthreads4w --- ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w)

message("  --- pthreads4w --- generate ---")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/pthreads4w -D BUILD_TESTING=OFF
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w
    OUTPUT_QUIET
    )

message("  --- pthreads4w --- build ---")
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w
    OUTPUT_QUIET
    )

message("  --- pthreads4w --- install ---")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config Debug --prefix ../out
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w
    OUTPUT_QUIET
    )

# pupnp
message("--- pupnp --- ${CMAKE_CURRENT_BINARY_DIR}/pupnp")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pupnp)

message("  --- pupnp --- generate ---")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/pupnp -D samples=OFF -D  DOWNLOAD_AND_BUILD_DEPS=OFF -D BUILD_TESTING=OFF -D ipv6=OFF -D PTHREADS4W_DIR=${CMAKE_CURRENT_BINARY_DIR}/out/lib/cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pupnp
    OUTPUT_QUIET
    )

message("  --- pupnp --- build ---")
execute_process(COMMAND ${CMAKE_COMMAND} --build . 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pupnp
    OUTPUT_QUIET
    )

message("  --- pupnp --- install ---")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config Debug --prefix ../out
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pupnp
    OUTPUT_QUIET
    )

# libebml
message("--- libebml --- ${CMAKE_CURRENT_BINARY_DIR}/libebml")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libebml)

message("  --- libebml --- generate ---")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/libebml -D BUILD_SHARED_LIBS=1 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libebml
    OUTPUT_QUIET
    )

message("  --- libebml --- build ---")
execute_process(COMMAND ${CMAKE_COMMAND} --build . 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libebml
    OUTPUT_QUIET
    )

message("  --- libebml --- install ---")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config Debug --prefix ../out
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libebml
    OUTPUT_QUIET
    )

# libmatroska
message("--- libmatroska --- ${CMAKE_CURRENT_BINARY_DIR}/libmatroska")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libmatroska)

message("  --- libmatroska --- generate ---")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/libmatroska -D EBML_DIR=${CMAKE_CURRENT_BINARY_DIR}/out/lib/cmake/EBML -D BUILD_SHARED_LIBS=1 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libmatroska
    OUTPUT_QUIET
    )

message("  --- libmatroska --- build ---")
execute_process(COMMAND ${CMAKE_COMMAND} --build . 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libmatroska
    OUTPUT_QUIET
    )

message("  --- libmatroska --- install ---")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config Debug --prefix ../out
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libmatroska
    OUTPUT_QUIET
    )

# flac
message("--- flac --- ${CMAKE_CURRENT_BINARY_DIR}/flac")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flac)

message("  --- flac --- generate ---")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/flac -D BUILD_PROGRAMS=OFF -D BUILD_EXAMPLES=OFF -D BUILD_TESTING=OFF -D BUILD_CXXLIBS=OFF -D WITH_OGG=OFF -D BUILD_SHARED_LIBS=ON
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flac
    OUTPUT_QUIET
    )

message("  --- flac --- build ---")
execute_process(COMMAND ${CMAKE_COMMAND} --build . 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flac
    OUTPUT_QUIET
    )

message("  --- flac --- install ---")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config Debug --prefix ../out
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flac
    OUTPUT_QUIET
    )

# 



# pupnp
#message("CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
# message("PTHREADS4W_DIR = ${PTHREADS4W_DIR}")
# set(PTHREADS4W_DIR ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w)
# message("CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")
# message("PTHREADS4W_DIR = ${PTHREADS4W_DIR}")
# message("CMAKE_CURRENT_LIST_DIR = ${CMAKE_CURRENT_LIST_DIR}")

# set(DOWNLOAD_AND_BUILD_DEPS OFF)
# option(BUILD_TESTING "" OFF)
# set(BUILD_TESTING OFF CACHE BOOL "")
# option(samples "" OFF)
# set(samples OFF CACHE BOOL "")
# option(ipv6 "" OFF)
# set(ipv6 OFF CACHE BOOL "")

# set(PTHREADS4W_DIR ${CMAKE_CURRENT_BINARY_DIR}/out/lib/cmake)

# add_subdirectory(pupnp)



