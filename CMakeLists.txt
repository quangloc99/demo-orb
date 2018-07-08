cmake_minimum_required(VERSION 2.8)
project(DemoOrb)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_LIBS})

add_library(ORBSlam
  ORBextractor.cpp
)

add_executable(example example.cpp)
target_link_libraries(example ${OpenCV_LIBS} ORBSlam)
