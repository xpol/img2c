cmake_minimum_required (VERSION 2.6)
project (img2c)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/lib")

find_package(FreeImage REQUIRED)
include_directories(${FREEIMAGE_INCLUDE_PATH})
set(LIBS ${LIBS} ${FREEIMAGE_LIBRARY})

add_executable(img2c src/img2c.cpp)
target_link_libraries(img2c ${LIBS})
