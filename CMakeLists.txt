cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(turing3d CXX)

include_directories(src)

set(SRC_FILES 
	src/arrows.cpp
	src/instruction.cpp
	src/loader.cpp
	src/main.cpp
	src/renderer.cpp
	src/rulebook.cpp
	src/tape3d.cpp
	src/timer.cpp
	src/turingmachine3d.cpp)

set(HEADER_FILES
	src/arrows.h
	src/instruction.h
	src/loader.h
	src/renderer.h
	src/rulebook.h
	src/tape3d.h
	src/timer.h
	src/turingmachine3d.h
	src/typedefs.h
	src/vec3.h)

add_executable(turing3d ${SRC_FILES} ${HEADER_FILES})

# Add libraries
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(turing3d ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

set(CMAKE_CXX_FLAGS "-O2")
