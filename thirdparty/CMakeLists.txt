



# pthreads4w
# option (BUILD_TESTING "" OFF)
# set(BUILD_TESTING OFF CACHE BOOL "")
# add_subdirectory(pthreads4w)

# install(FILES "${CMAKE_CURRENT_BINARY_DIR}/pthreads4w/PTHREADS4WConfig.cmake"
#               "${CMAKE_CURRENT_BINARY_DIR}/pthreads4w/PTHREADS4WConfigVersion.cmake"
#         DESTINATION out
#         )

message("------+-CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w)
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/pthreads4w -D BUILD_TESTING=OFF
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w
    )
message("----++--CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w
    )
message("----+++-CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config Debug --prefix ../out
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w
    )

# pupnp
 message("CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
# message("PTHREADS4W_DIR = ${PTHREADS4W_DIR}")
# set(PTHREADS4W_DIR ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w)
# message("CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")
# message("PTHREADS4W_DIR = ${PTHREADS4W_DIR}")
# message("CMAKE_CURRENT_LIST_DIR = ${CMAKE_CURRENT_LIST_DIR}")

set(DOWNLOAD_AND_BUILD_DEPS OFF)
option(BUILD_TESTING "" OFF)
set(BUILD_TESTING OFF CACHE BOOL "")
option(samples "" OFF)
set(samples OFF CACHE BOOL "")
option(ipv6 "" OFF)
set(ipv6 OFF CACHE BOOL "")

set(PTHREADS4W_DIR ${CMAKE_CURRENT_BINARY_DIR}/out/lib/cmake)

add_subdirectory(pupnp)



