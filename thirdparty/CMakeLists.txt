
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
if (UPDATE_DEPS OR PREPARE_DEPS)
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


# --- build deps ---
# pthreads4w
message("--- pthreads4w --- ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w)

message("  --- pthreads4w - generate")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/pthreads4w -D BUILD_TESTING=OFF
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w
    OUTPUT_QUIET
    )

message("  --- pthreads4w - build")
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w
    OUTPUT_QUIET
    )

message("  --- pthreads4w - install")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config Debug --prefix ../out
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pthreads4w
    OUTPUT_QUIET
    )

# pupnp
message("--- pupnp --- ${CMAKE_CURRENT_BINARY_DIR}/pupnp")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pupnp)

message("  --- pupnp - generate")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/pupnp -D samples=OFF -D  DOWNLOAD_AND_BUILD_DEPS=OFF -D BUILD_TESTING=OFF -D ipv6=OFF -D PTHREADS4W_DIR=${CMAKE_CURRENT_BINARY_DIR}/out/lib/cmake
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pupnp
    OUTPUT_QUIET
    )

message("  --- pupnp - build")
execute_process(COMMAND ${CMAKE_COMMAND} --build . 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pupnp
    OUTPUT_QUIET
    )

message("  --- pupnp - install")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config Debug --prefix ../out
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/pupnp
    OUTPUT_QUIET
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
execute_process(COMMAND ${CMAKE_COMMAND} --build . 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libebml
    OUTPUT_QUIET
    )

message("  --- libebml - install")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config Debug --prefix ../out
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libebml
    OUTPUT_QUIET
    )

# libmatroska
message("--- libmatroska --- ${CMAKE_CURRENT_BINARY_DIR}/libmatroska")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libmatroska)

message("  --- libmatroska - generate")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/libmatroska -D EBML_DIR=${CMAKE_CURRENT_BINARY_DIR}/out/lib/cmake/EBML -D BUILD_SHARED_LIBS=1 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libmatroska
    OUTPUT_QUIET
    )

message("  --- libmatroska - build")
execute_process(COMMAND ${CMAKE_COMMAND} --build . 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libmatroska
    OUTPUT_QUIET
    )

message("  --- libmatroska - install")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config Debug --prefix ../out
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/libmatroska
    OUTPUT_QUIET
    )

# flac
message("--- flac --- ${CMAKE_CURRENT_BINARY_DIR}/flac")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flac)

message("  --- flac - generate")
execute_process(COMMAND ${CMAKE_COMMAND} ${CMAKE_CURRENT_SOURCE_DIR}/flac -D BUILD_PROGRAMS=OFF -D BUILD_EXAMPLES=OFF -D BUILD_TESTING=OFF -D BUILD_CXXLIBS=OFF -D WITH_OGG=OFF -D BUILD_SHARED_LIBS=ON
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flac
    OUTPUT_QUIET
    )

message("  --- flac - build")
execute_process(COMMAND ${CMAKE_COMMAND} --build . 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flac
    OUTPUT_QUIET
    )

message("  --- flac - install")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config Debug --prefix ../out
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/flac
    OUTPUT_QUIET
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
execute_process(COMMAND ${CMAKE_COMMAND} --build . 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sqlite
    OUTPUT_QUIET
    )

message("  --- sqlite - install")
execute_process(COMMAND ${CMAKE_COMMAND} --install . --config Debug --prefix ../out
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/sqlite
    OUTPUT_QUIET
    )
# 




