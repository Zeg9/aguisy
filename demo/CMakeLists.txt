cmake_minimum_required(VERSION 2.6)

project(AGuiSy-demo)

SET(CMAKE_MODULE_PATH "${AGuiSy-demo_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(AGuiSy REQUIRED)
link_libraries(
	${OPENGL_LIBRARY}
	${GLEW_LIBRARY}
	${SDL_LIBRARY}
	${SDL_IMAGE_LIBRARY}
	${AGUISY_LIBRARY}
)

file(
	GLOB_RECURSE
	sources
	src/*.cpp
	include/*.h
)

include_directories(include)
add_executable(aguisy-demo ${sources})

install(TARGETS aguisy-demo DESTINATION bin)

