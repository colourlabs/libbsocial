cmake_minimum_required(VERSION 3.12)
project(libbsocial C)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

include(CheckCSourceCompiles)
include(CMakePushCheckState)
include(GNUInstallDirs)
include(GenerateExportHeader)

option(BUILD_SHARED_LIBS "Build as a shared library" TRUE)
option(EXAMPLES "Build examples" TRUE)

add_subdirectory(core)
if(EXAMPLES)
	message("hello?")
	add_subdirectory(examples)
endif()
