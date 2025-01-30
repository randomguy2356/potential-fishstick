cmake_minimum_required(VERSION 3.10)

project(potential-fishstick)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
endif()

add_executable(opengl main.cpp glad.c)
target_compile_options(opengl PRIVATE -W -Wall -Wextra)
target_link_libraries(opengl pthread Xrandr Xi dl GL X11 glfw)
