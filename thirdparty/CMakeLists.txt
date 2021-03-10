



# # pthreads4w
# option (BUILD_TESTING "" OFF)
# set(BUILD_TESTING OFF CACHE BOOL "")
# add_subdirectory(pthreads4w)

# pupnp
# message("CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
# message("PTHREADS4W_DIR = ${PTHREADS4W_DIR}")
# set(PTHREADS4W_DIR ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w)
# message("CMAKE_PREFIX_PATH = ${CMAKE_PREFIX_PATH}")
# message("PTHREADS4W_DIR = ${PTHREADS4W_DIR}")
# message("CMAKE_CURRENT_LIST_DIR = ${CMAKE_CURRENT_LIST_DIR}")

set(DOWNLOAD_AND_BUILD_DEPS ON)
option (BUILD_TESTING "" OFF)
set(BUILD_TESTING OFF CACHE BOOL "")
option (samples "" OFF)
set(samples OFF CACHE BOOL "")
add_subdirectory(pupnp)



