
cmake_minimum_required (VERSION 3.18)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project (proejct-name LANGUAGES C CXX)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake_modules)

option(OPT1 "description" ON)
add_subdirectory(subdir)


message(STATUS "msg...")


ADD_CUSTOM_COMMAND(
          TARGET targetname 
          POST_BUILD
          COMMAND cp ./someobject  ../
) 
