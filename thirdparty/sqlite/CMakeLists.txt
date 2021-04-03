cmake_minimum_required(VERSION 3.0)

# dwonload sqlite3 source zip (sqlite-amalgamation-xxxx.zip) from official site.
# extract the zip here, rename output directory "sqlite-amalgamation".

project (sqlite)

add_library(sqlite SHARED 
    sqlite-amalgamation/sqlite3.c
    )

target_compile_definitions(sqlite 
    PUBLIC "SQLITE_API=__declspec(dllexport)"
    )    

target_include_directories(sqlite 
    PUBLIC sqlite-amalgamation
    )

install(TARGETS sqlite DESTINATION bin)
install(FILES sqlite-amalgamation/sqlite3.h sqlite-amalgamation/sqlite3ext.h 
    DESTINATION include/sqlite
    )


