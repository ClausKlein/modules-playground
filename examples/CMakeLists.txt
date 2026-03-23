#
# from https://clang.llvm.org/docs/StandardCPlusPlusModules.html#quick-start
# A more complex “hello world” example which uses the 4 kinds of module units:
#
cmake_minimum_required(VERSION 4.2...4.3)

project(examples DESCRIPTION "Examples for Modules" LANGUAGES CXX)

add_library(play_hello STATIC)
add_library(play::play_hello ALIAS play_hello)

target_sources(
    play_hello
    PRIVATE impl.cpp impl_part.cpp
    PUBLIC FILE_SET CXX_MODULES FILES M.cppm interface_part.cppm
)
target_compile_features(play_hello PRIVATE cxx_std_23)

add_executable(example.user ../tests/user.cpp)
target_link_libraries(example.user PRIVATE play_hello)
add_test(NAME example.user COMMAND example.user)

if(CMAKE_CXX_MODULE_STD)
    target_compile_definitions(play_hello PUBLIC PLAY_HAS_IMPORT_STD)
    set_target_properties(example.user PROPERTIES CXX_MODULE_STD ON)
    set_target_properties(play_hello PROPERTIES CXX_MODULE_STD ON)
    message(STATUS "Build play_hello with target PROPERTY CXX_MODULE_STD ON")
endif()
