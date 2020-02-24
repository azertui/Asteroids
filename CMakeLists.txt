cmake_minimum_required(VERSION 3.6)

project(Projet_Asteroid LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

################################################################################
# App Settings 
################################################################################

set(GCC_OPT "-Wall -Wextra")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_OPT}")
include_directories(inc/)

################################################################################
# App binary
set(APP_BIN asteroid)
file(GLOB_RECURSE SRC LIST_DIRECTORIES true src/*.cpp)
add_executable(${APP_BIN} ${SRC})
target_include_directories(${APP_BIN} PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(${APP_BIN} PUBLIC ${SDL2_LIBRARIES})