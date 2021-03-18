cmake_minimum_required(VERSION 3.20)

project(templates_test LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(SRC_LIST

	src/args_printer.cpp
	src/apply.cpp
	src/array_type.cpp
	src/define_func_type.cpp
	src/enable_if.cpp
	src/func_traits.cpp
	src/has_member.cpp
	src/is_any_of.cpp
	src/is_pointer.cpp
	src/is_unique.cpp
	src/limit_types.cpp
	src/list.cpp
	src/not.cpp
	src/other_copy_ctor.cpp
	src/overload.cpp
	src/partial_spec.cpp
	src/str.cpp
	src/unroll.cpp
	src/values_list.cpp
)

add_subdirectory(src/common)

foreach(srcfile ${SRC_LIST})
	get_filename_component(target "${srcfile}" NAME_WE)
	add_executable(${target} ${srcfile})

	target_compile_features(${target} PRIVATE cxx_std_17)
	set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)

	if (MSVC)
		target_compile_options(${target} PRIVATE /W4)
	else()
		target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
	endif()

	target_link_libraries(${target} common)
endforeach()