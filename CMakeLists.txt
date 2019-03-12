cmake_minimum_required(VERSION 2.8)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")

include_directories("include/")
add_subdirectory(src)
add_executable(Main main.cpp)
target_link_libraries(Main src)
