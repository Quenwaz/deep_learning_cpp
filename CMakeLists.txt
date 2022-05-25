# CMakeList.txt : CMake project for deep_learning_cpp, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.18)


# CMAKE Pin cxx compiler to CXX14 until update to CXX17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_SYSTEM_VERSION 10.0.19041.0)

project(deep_learning_cpp LANGUAGES C CXX)
include(GNUInstallDirs)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake_modules)
include(utils)

option(deep_learning_cpp_BUILD_TESTS "build tests alongside the project" ON)
add_subdirectory(src)

# TODO: Add tests and install targets if needed.

if (deep_learning_cpp_BUILD_TESTS)
    include(CTest)
    find_package(GTest QUIET)
    if (NOT GTEST_FOUND)
        message("GoogleTest not found. Consider installing it on your system. Downloading it from source...")
        include(FetchContent)
        set(FETCHCONTENT_QUIET OFF)
        # 设置依赖目录
        get_filename_component(deps "../deps" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
        set(FETCHCONTENT_BASE_DIR ${deps})
        FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://gitee.com/mirrors/googletest.git
            # GIT_TAG release-1.10.0
            GIT_SHALLOW true
        )
         
        set(BUILD_GMOCK OFF CACHE BOOL "")
        FetchContent_GetProperties(googletest)
        if(NOT googletest_POPULATED)
            FetchContent_Populate(googletest)
            add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
        endif()
    endif()
    add_subdirectory(tests)
endif()

message(STATUS INCLUDE_DIRECTORIES=${INCLUDE_DIRECTORIES})
