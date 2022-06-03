cmake_minimum_required(VERSION 3.22)
project(zachet)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(zachet
        main.cpp classes/Person/Person.cpp classes/Person/Person.h classes/Util/Util.cpp classes/Util/Util.h classes/PersonList/PersonList.cpp classes/PersonList/PersonList.h)
