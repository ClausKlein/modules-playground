cmake_minimum_required(VERSION 4.2...4.3)

project(tests LANGUAGES CXX)

if(PROJECT_IS_TOP_LEVEL)
    find_package(modules_playground 0.1.0 EXACT REQUIRED)

    if(${CMAKE_CXX_STANDARD} IN_LIST CMAKE_CXX_COMPILER_IMPORT_STD)
        set(CMAKE_CXX_MODULE_STD 1)
        message(STATUS "Using `import std;`")
    endif()

    enable_testing()
endif()

add_executable(test.main main.cpp)
target_compile_features(test.main PUBLIC cxx_std_23)
target_link_libraries(test.main PUBLIC play::play_mylib)

add_test(NAME test.main COMMAND test.main)

add_executable(test.user user.cpp)
target_link_libraries(test.user PRIVATE play::play_hello)
add_test(NAME test.user COMMAND test.user)

if(CMAKE_CXX_MODULE_STD)
    set_target_properties(test.user PROPERTIES CXX_MODULE_STD ON)
    set_target_properties(test.main PROPERTIES CXX_MODULE_STD ON)
    message(STATUS "Build test.main with target PROPERTY CXX_MODULE_STD ON")
endif()
