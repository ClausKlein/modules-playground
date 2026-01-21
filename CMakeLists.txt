cmake_minimum_required(VERSION 3.28..4.2)
project(mytest LANGUAGES CXX)

# add_library(mylib)
# target_sources(
#     mylib
#     PUBLIC FILE_SET CXX_MODULES FILES lib.cpp
# )
# target_compile_features(mylib PUBLIC cxx_std_23)
# set_target_properties(mylib PROPERTIES CXX_MODULE_STD ON)

add_executable(main main.cpp)
target_compile_features(main PUBLIC cxx_std_23)
set_target_properties(main PROPERTIES CXX_MODULE_STD ON)

