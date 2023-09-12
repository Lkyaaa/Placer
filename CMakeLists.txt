cmake_minimum_required(VERSION 3.22)
project(Placer)

set(CMAKE_CXX_STANDARD 17)


add_executable(Placer main.cpp database/database.h parser/parser.h parser/parser.cpp placement/placement.h placement/placement.cpp exporter/exporter.h exporter/exporter.cpp)


target_include_directories(Placer PRIVATE /usr/include/tclap)