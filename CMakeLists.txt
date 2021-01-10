cmake_minimum_required(VERSION 3.15)
project(DS1_2020_Wet2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DS1_2020_Wet2
        # AVL_tests_OLD.h
        AvlTree.h
        Course.cpp
        Course.h
        CoursesManager.cpp
        CoursesManager.h
        HashTable.cpp
        HashTable.h
        library2.cpp
        library2.h
        List.cpp
        List.h
        main.cpp
        # main2.cpp
        MyClass.cpp
        MyClass.h)
