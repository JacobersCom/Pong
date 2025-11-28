add_library(Project

	includes/Defines.h
	includes/Game.h
	src/Game.cpp
	src/main.cpp
)

target_include_directories(Project
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/includes
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(Project
	PUBLIC
	SDL3::SDL3
)
