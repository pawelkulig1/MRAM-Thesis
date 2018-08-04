cmake_minimum_required(VERSION 3.8)
project(C___core)

set(CMAKE_CXX_STANDARD 11)

include_directories(Eigen/)

set(SOURCE_FILES
        image.h
        main.cpp
        myVector.cpp
        myVector.h
        planeFunction.h
        vector.cpp
        vector.h)

add_executable(C___core ${SOURCE_FILES})