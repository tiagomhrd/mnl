cmake_minimum_required(VERSION 3.23.1)

project(mnl)

add_library(${PROJECT_NAME} INTERFACE
${CMAKE_CURRENT_SOURCE_DIR}/include/mnl.hpp 
${CMAKE_CURRENT_SOURCE_DIR}/include/pnl.hpp 
${CMAKE_CURRENT_SOURCE_DIR}/include/glq.hpp 
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

add_subdirectory(third_party/Catch2)
add_subdirectory(tests)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tests)