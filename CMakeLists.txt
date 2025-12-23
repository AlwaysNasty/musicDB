cmake_minimum_required(VERSION 4.0)
project(musicDB C)

set(CMAKE_C_STANDARD 11)

add_executable(musicDB database.c
        database.h
        main.c
        menu.h
        menu.c)

if(MSVC)
    add_compile_options(/utf-8)
endif()
