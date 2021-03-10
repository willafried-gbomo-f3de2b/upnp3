


set(DOWNLOAD_AND_BUILD_DEPS ON)
option (BUILD_TESTING "Run Tests after compile" ON)
set(BUILD_TESTING OFF CACHE BOOL "")
option (samples "compilation of upnp/sample/ code" ON)
set(samples OFF CACHE BOOL "")

add_subdirectory(pupnp)

