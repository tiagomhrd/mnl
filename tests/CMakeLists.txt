cmake_minimum_required(VERSION 3.23.1)

project(tests)

add_executable(${PROJECT_NAME} 
${CMAKE_CURRENT_SOURCE_DIR}/src/tests.cpp 
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 23)

target_include_directories(${PROJECT_NAME} 
PRIVATE src 
PRIVATE ../include 
PRIVATE ../third_party/Catch2/ 
)

target_link_libraries(${PROJECT_NAME} 
Catch2 
)