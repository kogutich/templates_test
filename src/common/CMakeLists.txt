cmake_minimum_required(VERSION 3.20)

set(COMMON_SRC common.hpp)
add_library(common INTERFACE "${COMMON_SRC}")
target_include_directories(common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(common PROPERTIES FOLDER "Common lib")