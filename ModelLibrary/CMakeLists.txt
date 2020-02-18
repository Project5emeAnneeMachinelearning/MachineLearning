cmake_minimum_required(VERSION 2.8)
project(ModelLibrary)

SET(CMAKE_CXX_FLAGS "-std=gnu++11") #Turn on C++11 Support

add_subdirectory(lib/googletest-1.10.x)
include_directories(lib/googletest-1.10.x/googletest/include)
include_directories(lib/googletest-1.10.x/googlemock/include)
include_directories(BEFORE ${GTEST_INCLUDE_DIRS})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(SOURCE_FILES test/TestModel.cpp )
add_library (ModelLibrary SHARED Model.cpp test/TestModel.cpp)
set_property(TARGET gtest PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(ModelLibrary pthread gtest gtest_main)




