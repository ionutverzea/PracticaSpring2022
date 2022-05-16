cmake_minimum_required(VERSION 3.0)
project(ImageProcessingApp)

set( AppSources
	main.cpp
)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#======================= INCLUSION OF Qt =======================#
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(OpenCV REQUIRED)



add_executable(${PROJECT_NAME} ${AppSources})

add_dependencies(${PROJECT_NAME}
	Algorithms
	Utils
)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_SOURCE_DIR}/Algorithms
	${CMAKE_SOURCE_DIR}/Utils
	
)


target_link_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

target_link_libraries(${PROJECT_NAME}
	Qt5::Widgets
	Algorithms.lib
	Utils.lib
	${OpenCV_LIBS}
	
)



