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

add_executable(main main.cpp)
target_compile_features(main PUBLIC cxx_std_23)
target_link_libraries(main PUBLIC play::play_mylib)
set_target_properties(main PROPERTIES CXX_MODULE_STD ${CMAKE_CXX_MODULE_STD})

if(CMAKE_CXX_MODULE_STD)
    set_property(TARGET main PROPERTY CXX_MODULE_STD ON)
    message(STATUS "Build main with target PROPERTY CXX_MODULE_STD ON")
endif()

add_test(NAME main COMMAND main)
