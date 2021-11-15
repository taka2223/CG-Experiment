cmake_minimum_required(VERSION 3.0.0)
project(exp6 VERSION 0.1.0)

find_package(OpenGL REQUIRED)


# GLFW
find_package(glfw3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

# ASSIMP
find_package(ASSIMP REQUIRED)
message(STATUS "Found ASSIMP in ${ASSIMP_INCLUDE_DIR}")
include(CTest)
enable_testing()
# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)


add_executable(exp6 ${SOURCE_FILES} ${HEADER_FILDES})

include_directories(${OpenGL_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIR} ${ASSIMP_INCLUDE_DIR})

target_link_libraries(exp6 glfw3 GL -lGL -lm -ldl -lXinerama -lXrandr -lXi -lXcursor -lX11 -lXxf86vm -lpthread -lassimp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
