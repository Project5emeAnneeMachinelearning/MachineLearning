project(machine_learning_lib)

set(CMAKE_CXX_STANDARD 14)

add_library(machine_learning_lib SHARED Model.cpp Model.h MultiLayer.cpp MultiLayer.h)
add_executable(machine_learning_exe Model.cpp Model.h MultiLayer.cpp MultiLayer.h API.cpp API.h)


