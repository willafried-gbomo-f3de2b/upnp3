


set(DOWNLOAD_AND_BUILD_DEPS ON)
option (BUILD_TESTING "Run Tests after compile" OFF)
set(BUILD_TESTING OFF CACHE BOOL "")
option (samples "compilation of upnp/sample/ code" OFF)
set(samples OFF CACHE BOOL "")
set(CTEST_CONFIGURATION_TYPE )

add_subdirectory(pupnp)

