cmake_minimum_required(VERSION 3.0)

project(deps)

# VS CRT Options
string(REGEX REPLACE " */M[TD]d? *" " " CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
string(REGEX REPLACE " */M[TD]d? *" " " CMAKE_C_FLAGS_Debug "${CMAKE_C_FLAGS_Debug}")
string(REGEX REPLACE " */M[TD]d? *" " " CMAKE_C_FLAGS_Release "${CMAKE_C_FLAGS_Release}")
string(REGEX REPLACE " */M[TD]d? *" " " CMAKE_C_FLAGS_RelWithDebInfo "${CMAKE_C_FLAGS_RelWithDebInfo}")

string(APPEND CMAKE_C_FLAGS_Debug "/MDd")
string(APPEND CMAKE_C_FLAGS_Release "/MD")
string(APPEND CMAKE_C_FLAGS_RelWithDebInfo "/MD")

message("CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")
message("CMAKE_C_FLAGS_Debug: ${CMAKE_C_FLAGS_Debug}")
message("CMAKE_C_FLAGS_Release: ${CMAKE_C_FLAGS_Release}")
message("CMAKE_C_FLAGS_RelWithDebInfo: ${CMAKE_C_FLAGS_RelWithDebInfo}")

# --- clone dependencies ---
if (PREPARE_DEPS)
    message("--- cleaning deps directory ---")
    file(REMOVE_RECURSE 
        pthreads4w 
        pupnp 
        libebml 
        libmatroska
        flac
        )

    message("--- cloning deps ---")
    message("  --- pupnp ---")
    execute_process(COMMAND git clone https://github.com/pupnp/pupnp.git
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
        )
    message("  --- pthreads4w ---")
    execute_process(COMMAND git clone https://github.com/Vollstrecker/pthreads4w.git
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
        )
    message("  --- libebml ---")
    execute_process(COMMAND git clone https://github.com/Matroska-Org/libebml.git
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
        )
    message("  --- libmatroska ---")
    execute_process(COMMAND git clone https://github.com/Matroska-Org/libmatroska.git
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
        )
    message("  --- flac ---")
    execute_process(COMMAND git clone https://github.com/xiph/flac.git
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} 
        )
    message("  --- sqlite needed.")

endif()


# --- update dependencies ---
if (UPDATE_DEPS)
    message("--- updating deps ---")
    message("  --- pthreads4w ---")
    execute_process(COMMAND git pull 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pthreads4w 
        )
    message("  --- pupnp ---")
    execute_process(COMMAND git pull 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/pupnp 
        )
    message("  --- libebml ---")
    execute_process(COMMAND git pull 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libebml 
        )
    message("  --- libmatroska ---")
    execute_process(COMMAND git pull 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libmatroska 
        )
    message("  --- flac ---")
    execute_process(COMMAND git pull 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/MAKE_CURRENT_BINARY_DIR}/flac 
        )
    message("  --- sqlite update needed.")
endif()


# BUILD -------------------------------
if(BUILD_DEPS)
# --- build deps ---
message("--- building deps: BUILD_TYPE=${BUILD_TYPE} --- ${CMAKE_CURRENT_BINARY_DIR}")
file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/outtmp)

# pthreads4w ---
message("--- pthreads4w --- ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w)

if(${BUILD_TYPE} STREQUAL "RelWithDebInfo" OR ${BUILD_TYPE} STREQUAL "Release")
    set(BT "Release")
else()
    set(BT "Debug")
endif()

message("  --- pthreads4w - generate")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/pthreads4w -D BUILD_TESTING=OFF
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w
    OUTPUT_QUIET
    )

message("  --- pthreads4w - build")
execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${BT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w
    OUTPUT_QUIET
    )

message("  --- pthreads4w - install")
file(REMOVE ${CMAKE_CURRENT_BINARY_DIR}/outtmp)
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config ${BT} --prefix ../outtmp
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w
    OUTPUT_QUIET
    )

# pupnp ---
message("--- pupnp --- ${CMAKE_CURRENT_BINARY_DIR}/pupnp")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pupnp)

if(${BUILD_TYPE} STREQUAL "RelWithDebInfo" OR ${BUILD_TYPE} STREQUAL "Release")
    set(BT "Release")
else()
    set(BT "Debug")
endif()

message("  --- pupnp - generate")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/pupnp -D samples=OFF -D  DOWNLOAD_AND_BUILD_DEPS=OFF -D BUILD_TESTING=OFF -D ipv6=OFF -D PTHREADS4W_DIR=${CMAKE_CURRENT_BINARY_DIR}/outtmp/lib/cmake 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pupnp
    #OUTPUT_QUIET
    OUTPUT_VARIABLE OUTSTDVAR
    #ERROR_VARIABLE OUTERRVAR
    )

message("  --- pupnp - build")
execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${BT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pupnp
    #OUTPUT_QUIET
    OUTPUT_VARIABLE OUTSTDVAR
    #ERROR_VARIABLE OUTERRVAR
    )

message("  --- pupnp - install")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config ${BT} --prefix ../outtmp
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pupnp
    #OUTPUT_QUIET
    OUTPUT_VARIABLE OUTSTDVAR
    #ERROR_VARIABLE OUTERRVAR
    )

# libebml
message("--- libebml --- ${CMAKE_CURRENT_BINARY_DIR}/libebml")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libebml)

message("  --- libebml - generate")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/libebml -D BUILD_SHARED_LIBS=1 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libebml
    OUTPUT_QUIET
    )

message("  --- libebml - build")
execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${BUILD_TYPE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libebml
    OUTPUT_QUIET
    )

message("  --- libebml - install")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config ${BUILD_TYPE} --prefix ../outtmp
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libebml
    OUTPUT_QUIET
    )

# libmatroska
message("--- libmatroska --- ${CMAKE_CURRENT_BINARY_DIR}/libmatroska")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libmatroska)

message("  --- libmatroska - generate")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/libmatroska -D EBML_DIR=${CMAKE_CURRENT_BINARY_DIR}/outtmp/lib/cmake/EBML -D BUILD_SHARED_LIBS=1
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libmatroska
    OUTPUT_QUIET
    )

message("  --- libmatroska - build")
execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${BUILD_TYPE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libmatroska
    OUTPUT_QUIET
    )

message("  --- libmatroska - install")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config ${BUILD_TYPE} --prefix ../outtmp WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libmatroska
    OUTPUT_QUIET
    )

# flac
message("--- flac --- ${CMAKE_CURRENT_BINARY_DIR}/flac")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flac)

message("  --- flac - generate")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/flac -D BUILD_PROGRAMS=OFF -D BUILD_EXAMPLES=OFF -D BUILD_TESTING=OFF -D BUILD_CXXLIBS=OFF -D WITH_OGG=OFF -D BUILD_SHARED_LIBS=ON
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flac
    #OUTPUT_QUIET
    OUTPUT_VARIABLE OUTSTDVAR
    #ERROR_VARIABLE OUTERRVAR
    )

message("  --- flac - build")
execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${BUILD_TYPE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flac
    #OUTPUT_QUIET
    OUTPUT_VARIABLE OUTSTDVAR
    #ERROR_VARIABLE OUTERRVAR
    )

message("  --- flac - install")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config ${BUILD_TYPE} --prefix ../outtmp
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flac
    #OUTPUT_QUIET
    OUTPUT_VARIABLE OUTSTDVAR
    #ERROR_VARIABLE OUTERRVAR
    )

# sqlite
message("--- sqlite --- ${CMAKE_CURRENT_BINARY_DIR}/sqlite")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sqlite)

message("  --- sqlite - generate")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/sqlite
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sqlite
    OUTPUT_QUIET
    )

message("  --- sqlite - build")
execute_process(COMMAND ${CMAKE_COMMAND} --build . --config ${BUILD_TYPE}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sqlite
    OUTPUT_QUIET
    )

message("  --- sqlite - install")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config ${BUILD_TYPE} --prefix ../outtmp
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sqlite
    OUTPUT_QUIET
    )

# copy ---
message("--- copying ---")

file(GLOB OUT 
    ${CMAKE_CURRENT_BINARY_DIR}/outtmp/lib/*.lib
    ${CMAKE_CURRENT_BINARY_DIR}/outtmp/bin/*.lib
    )
#message("  --- LIBS: ${OUT}")
file(COPY ${OUT} DESTINATION ${OUT_LIB_PREFIX})

file(GLOB OUT 
    ${CMAKE_CURRENT_BINARY_DIR}/outtmp/lib/*.dll
    ${CMAKE_CURRENT_BINARY_DIR}/outtmp/bin/*.dll
    )
#message("  --- BINS: ${OUT}")
file(COPY ${OUT} DESTINATION ${OUT_BIN_PREFIX})

file(GLOB OUT LIST_DIRECTORIES true
    ${CMAKE_CURRENT_BINARY_DIR}/outtmp/include/*
    )
file(COPY ${OUT} DESTINATION ${OUT_INC_PREFIX})

endif()
