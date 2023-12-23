cmake_minimum_required(VERSION 3.26)
project(AED_proj_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(AED_proj_2 src/main.cpp
        src/Application.cpp
        src/Application.h
        src/FileReader.cpp
        src/FileReader.h
        src/Airline.cpp
        src/Airline.h
        src/Airport.cpp
        src/Airport.h
        src/Graph.h
        src/Interface.cpp
        src/Interface.h
)
