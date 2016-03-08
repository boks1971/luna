cmake_minimum_required(VERSION 3.3)
project(luna_example)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include(conanbuildinfo.cmake)
conan_basic_setup()

set(SOURCE_FILES main.cpp)
add_executable(luna_example ${SOURCE_FILES})
target_link_libraries(luna_example ${CONAN_LIBS} microhttpd)
