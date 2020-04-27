cmake_minimum_required(VERSION 3.15)

Project(VolumeReadTest VERSION 1.0.0)

# Setup language options.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)

# Setup global compile options for all our projects.
if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	
	add_compile_options(
		"/utf-8"

		"/W3"
		"/WX"
		)

else()

	add_compile_options(
		"-Wall"
		"-Wextra"
		"-Wconversion"
		"-Werror"
		)
	
endif()

add_definitions(-D_CRT_SECURE_NO_WARNINGS)

add_executable(GetNetworkInterfaces main.cpp)