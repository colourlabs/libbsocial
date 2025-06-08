cmake_minimum_required(VERSION 3.12)
project(libbsocial C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(CheckCSourceCompiles)
include(CMakePushCheckState)
include(GNUInstallDirs)
include(GenerateExportHeader)
include(CMakeDependentOption)

set(CMAKE_C_STANDARD 90)

option(BUILD_SHARED_LIBS "Build as a shared library" ON)
option(BUILD_CURL "Build cURL module" ON)
CMAKE_DEPENDENT_OPTION(EXAMPLES "Build examples" ON "BUILD_CURL" OFF)

add_subdirectory(core)
if (BUILD_CURL) 
	add_subdirectory(curl)
endif()
if(EXAMPLES)
	add_subdirectory(examples)
endif()
