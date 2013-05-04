cmake_minimum_required(VERSION 2.6)
project(AGuiSy-lib)


file(
	GLOB_RECURSE
	includes
	include/AGuiSy/*.h
)

file(
	GLOB_RECURSE
	sources
	src/*.cpp
	${includes}
)

include_directories(include)
include_directories(include/AGuiSy)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
link_libraries(
	${OPENGL_LIBRARY}
	${GLEW_LIBRARY}
	${SDL_LIBRARY}
	${SDL_IMAGE_LIBRARY}
)
add_library(aguisy SHARED ${sources})
#add_library(aguisy_static STATIC ${sources})
install(FILES ${includes} DESTINATION include/AGuiSy)
install(TARGETS aguisy# aguisy_static
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)
