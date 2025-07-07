cmake_minimum_required(VERSION 3.0)
project(OCR)

set(PADDLE_LITE_DIR Paddle-Lite/build.lite.linux.x86.gcc/inference_lite_lib)
message(STATUS "Paddle Lite DIR: ${PADDLE_LITE_DIR}")
include_directories(${PADDLE_LITE_DIR}/cxx/include)
link_directories(${PADDLE_LITE_DIR}/cxx/lib)

find_package(OpenCV REQUIRED)
find_package(PkgConfig REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(OCR src/main.cpp)
target_link_libraries(OCR 
	${OpenCV_LIBS}
	paddle_full_api_shared  # или paddle_api_light
	iomp5
)
