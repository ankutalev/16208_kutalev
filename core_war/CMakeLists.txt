cmake_minimum_required(VERSION 3.8)
project(core_war)

set(CMAKE_CXX_STANDARD 11)

#set(SOURCE_FILES main.cpp heder.h loader.cpp loader.h mov_command.cpp warrior.hpp warrior.cpp instructions.cpp instructions.hpp)
set(SOURCE_FILES  heder.h loader.cpp loader.h mov_command.cpp warrior.hpp warrior.cpp instructions.cpp instructions.hpp)

add_executable(core_war ${SOURCE_FILES})