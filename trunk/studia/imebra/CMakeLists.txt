cmake_minimum_required(VERSION 2.8)

project("libimebra")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra -Wpedantic -pthread")

# Specify include and source files
#---------------------------------
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/library/imebra/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/library/base/include)

file(GLOB imebra_include_interface "${CMAKE_CURRENT_SOURCE_DIR}/library/imebra/include/*.h")
file(GLOB imebra_sources 
	"${CMAKE_CURRENT_SOURCE_DIR}/library/imebra/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/library/base/src/*.cpp"
)

# Add the source files to the project
#------------------------------------
add_library(imebra ${imebra_sources})


