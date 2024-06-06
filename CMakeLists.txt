cmake_minimum_required(VERSION 3.12)
project(ProjectFinal)

# Set the C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)


include_directories(include)

set (MAIN_SOURCES
    src/main.cpp
    src/tracker.cpp
    src/graphical_interface.cpp
)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(main ${MAIN_SOURCES})
target_link_libraries(main ${OpenCV_LIBS})

