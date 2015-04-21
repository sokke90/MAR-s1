# define new project
PROJECT(MAR_Test)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.0 FATAL_ERROR)

if(UNIX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(UNIX)

# Set static build for GLFW
SET(BUILD_SHED_LIBS OFF)
ADD_SUBDIRECTORY(ext/glfw-3.1.1)

# Set shared lib build for the rest
SET(BUILD_SHARED_LIBS ON)

# Find dependencies
SET(EIGEN_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/ext/Eigen-3.1.2")
FIND_PACKAGE(OpenCV REQUIRED)

# Set header and source files
SET(MAR_Test_SOURCES
    src/main.cpp
)

# define executable
ADD_EXECUTABLE(${PROJECT_NAME} ${MAR_Test_SOURCES})

# define additional include directories and linking targets
INCLUDE_DIRECTORIES("ext/glfw-3.1.1/include" ${EIGEN_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS} glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES})