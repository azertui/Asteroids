cmake_minimum_required(VERSION 3.6)

project(Projet_Asteroid LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(SDL2-2.0.10/)

################################################################################
# App Settings 
################################################################################

set(GCC_OPT "-Wall -Wextra")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_OPT}")
include_directories(include/)

################################################################################
# App binary
set(APP_BIN asteroid)
file(GLOB_RECURSE SRC LIST_DIRECTORIES true src/*.cpp)
add_executable(${APP_BIN} ${SRC})
target_link_libraries(${APP_BIN} PUBLIC SDL2main SDL2-static)