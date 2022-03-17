cmake_minimum_required(VERSION 3.5)

project(relf VERSION 0.1)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(OPTIMIZATIONS ON)
set(DEBUGGER OFF)
set(NO_FLAG ON)

if(OPTIMIZATIONS)
    set(CMAKE_CXX_FLAGS "-mavx -fno-stack-protector -march=native -O2 -Os -fdelete-null-pointer-checks -fdelete-dead-exceptions")
        if(DEBUGGER)
            set(CMAKE_CXX_FLAGS "-g -gdwarf -gdwarf-version")
        endif()
    if(NO_FLAG)
        set(CMAKE_CXX_FLAGS " ")
    endif()
endif()


set(PROJECT_SOURCES

	src/main.c

	src/include/relf.c
	src/include/relf.h

)
add_executable(relf ${PROJECT_SOURCES} )
