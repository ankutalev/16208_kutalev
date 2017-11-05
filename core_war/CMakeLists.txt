cmake_minimum_required(VERSION 3.8)
project(core_war)

set(CMAKE_CXX_STANDARD 11)

#set(SOURCE_FILES main.cpp heder.h loader.cpp loader.h mov_command.cpp warrior.hpp warrior.cpp instructions.cpp instructions.hpp)
set(SOURCE_FILES  heder.h loader.cpp loader.h mov_command.cpp warrior.hpp warrior.cpp instructions.cpp instructions.hpp CircularBuffer.hpp CircularBuffer.cpp add_command.cpp jmp_command.cpp factory.cpp factory.hpp dat_command.cpp sub_command.cpp mul_command.cpp div_command.cpp jmz_command.cpp spl_command.cpp seq_command.cpp jmn_command.cpp sne_command.cpp slt_command.cpp nop_command.cpp)

add_executable(core_war ${SOURCE_FILES})