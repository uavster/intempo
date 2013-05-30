cmake_minimum_required(VERSION 2.6)
project(INTEMPO_EXAMPLE_NORMAL)

find_package(ATLANTE)
include_directories(${ATLANTE_INCLUDE_DIRS})
link_libraries(${ATLANTE_LIBRARIES})

#
# In your project using Intempo, you should replace the single include_directories command with the following two lines:
# find_package(INTEMPO)
# include_directories(${INTEMPO_INCLUDE_DIRS})
#
include_directories(../../intempo)

add_executable(test test.cpp)

