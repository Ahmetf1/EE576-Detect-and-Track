cmake_minimum_required(VERSION 3.12)
project(ProjectFinal)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ONNX_RUNTIME_PATH "/opt/onnxruntime" CACHE STRING "ONNX Runtime directory path")
set(CUDA_LIBRARIES_PATH "/opt/cuda11" CACHE STRING "CUDA libraries path compatible with the ONNX Runtime")

add_library(onnxruntime SHARED IMPORTED)
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    message(FATAL_ERROR "Unsupported target platform. Believe me, you don't want to use Windows for this project.")
elseif(UNIX)
	set(ONNX_IMPORTED_LOCATION "${ONNX_RUNTIME_PATH}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}onnxruntime${CMAKE_SHARED_LIBRARY_SUFFIX}")
	set(ONNX_INTERFACE_INCLUDE_DIRECTORIES "${ONNX_RUNTIME_PATH}/include")
	if(NOT EXISTS ${ONNX_IMPORTED_LOCATION})
		message(FATAL_ERROR "Excepted Onnxruntime library '${ONNX_IMPORTED_LOCATION}' does not exist. Please specify a valid ONNX_RUNTIME_PATH.(current: ${ONNX_RUNTIME_PATH})")
	endif()
	if(NOT EXISTS ${ONNX_INTERFACE_INCLUDE_DIRECTORIES})
		message(FATAL_ERROR "Excepted Onnxruntime include directory '${ONNX_INTERFACE_INCLUDE_DIRECTORIES}' does not exist. Please specify a valid ONNX_RUNTIME_PATH.(current: ${ONNX_RUNTIME_PATH})")
	endif()
	
    set_target_properties(onnxruntime PROPERTIES
        IMPORTED_LOCATION ${ONNX_IMPORTED_LOCATION}
        INTERFACE_INCLUDE_DIRECTORIES ${ONNX_INTERFACE_INCLUDE_DIRECTORIES}
    )
else()
	message(FATAL_ERROR "Unsupported target platform. Use linux it is better.")
endif()




include_directories(include)

set (MAIN_SOURCES
    src/main.cpp
    src/tracker.cpp
    src/graphical_interface.cpp
    src/yolov7_cxx.cpp
    src/constants.cpp
    src/dataset.cpp
)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(main ${MAIN_SOURCES})
target_link_libraries(main ${OpenCV_LIBS} onnxruntime)

