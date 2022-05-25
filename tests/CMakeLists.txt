function(deep_learning_cpp_test test_name)
    set(TEST_EXECUTABLE run_${test_name})
    set(TEST_SOURCE ${test_name}.cpp)

    add_executable(${TEST_EXECUTABLE} ${TEST_SOURCE})
    target_include_directories(${TEST_EXECUTABLE} PRIVATE ${PROJECT_SOURCE_DIR}/include)
    # CMake 3.20 and upstream GTest define GTest::gtest, older versions define GTest::GTest
    if (TARGET GTest::gtest)
        target_link_libraries(${TEST_EXECUTABLE} GTest::gtest GTest::gtest_main ${PROJECT_NAME}_static)
    else ()
        target_link_libraries(${TEST_EXECUTABLE} GTest::GTest GTest::Main ${PROJECT_NAME}_static)
    endif ()
    target_compile_definitions(${TEST_EXECUTABLE} PRIVATE _GLIBCXX_USE_CXX11_ABI=0)
    add_test(${test_name} ${TEST_EXECUTABLE})
endfunction()


get_current_filename(tests ${CMAKE_CURRENT_SOURCE_DIR})
foreach(test ${tests})
    deep_learning_cpp_test(${test})
endforeach(test ${tests})
