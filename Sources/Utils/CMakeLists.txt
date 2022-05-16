cmake_minimum_required(VERSION 3.0)
project(Utils)

set(LibrarySources
	Utils.h
	Utils.cpp
)



add_definitions(-DUTILS_EXPORT)

#======================= INCLUSION OF Qt =======================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(OpenCV REQUIRED)

add_library(${PROJECT_NAME} SHARED ${LibrarySources})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets
		      ${OpenCV_LIBS}
		      )
