function(metaprogramming_test test_name)
    set(TEST_EXECUTABLE run_${test_name})
    set(TEST_SOURCE ${test_name}.cpp)

    add_executable(${TEST_EXECUTABLE} ${TEST_SOURCE})
    target_include_directories(${TEST_EXECUTABLE} PRIVATE ${PROJECT_SOURCE_DIR}/include)
    # CMake 3.20 and upstream GTest define GTest::gtest, older versions define GTest::GTest
    if (TARGET GTest::gtest)
        target_link_libraries(${TEST_EXECUTABLE} GTest::gtest GTest::gtest_main)
    else ()
        target_link_libraries(${TEST_EXECUTABLE} GTest::GTest GTest::Main)
    endif ()
    target_compile_definitions(${TEST_EXECUTABLE} PRIVATE _GLIBCXX_USE_CXX11_ABI=0)
    add_test(${test_name} ${TEST_EXECUTABLE})
endfunction()


get_current_filename(tests ${CMAKE_CURRENT_SOURCE_DIR})
foreach(test ${tests})
    metaprogramming_test(${test})
endforeach(test ${tests})
