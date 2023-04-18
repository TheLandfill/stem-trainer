cmake_minimum_required(VERSION 3.0.0)
project(test)

#add_compile_options(-fsanitize=address)
#add_link_options(-fsanitize=address)
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.c*")
add_executable(test ${SOURCES})
