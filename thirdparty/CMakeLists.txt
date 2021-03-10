
# pupnp
if (REBUILD_ALL)
set(DOWNLOAD_AND_BUILD_DEPS ON)
option (BUILD_TESTING "Run Tests after compile" ON)
set(BUILD_TESTING ON CACHE BOOL "")
option (samples "compilation of upnp/sample/ code" ON)
set(samples ON CACHE BOOL "")
else()
set(DOWNLOAD_AND_BUILD_DEPS OFF)
option (BUILD_TESTING "Run Tests after compile" OFF)
set(BUILD_TESTING OFF CACHE BOOL "")
option (samples "compilation of upnp/sample/ code" OFF)
set(samples OFF CACHE BOOL "")
endif()

add_subdirectory(pupnp)

