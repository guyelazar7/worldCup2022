cmake_minimum_required(VERSION 3.21)
project(miv2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(miv2
        main23a2.cpp
        wet2util.h
        Exception.h
        HashTable.cpp
        HashTable.h
        NewTree.h
        Player.cpp
        Player.h
        PlayerStack.h
        Team.cpp
        Team.h
        worldcup23a2.cpp
        worldcup23a2.h)
