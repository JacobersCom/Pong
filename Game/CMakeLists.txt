
add_executable(Pong main.cpp)

target_link_libraries(Pong PRIVATE Project)


set(
	CMAKE_RUNTIME_OUTPUT_DIRECTORY
	"${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)
set(
	CMAKE_LIBRARY_OUTPUT_DIRECTORY
	"${CMAKE_BINARY_DIR}/$<CONFIGURATION>"
)

if(APPLE)
	set_target_properties(Pong PROPERTIES
	INSTALL_RPATH "@executable_path;@loader_path"
	BUILD_WITH_INSTALL_RPATH TRUE
	MACOSX_RPATH TRUE
	)
elseif(UNIX)
	set_target_properties(Pong PROPERTIES
	INSTALL_RPATH "@ORIGIN"
	BUILD_WITH_INSTALL_RPATH TRUE
	)
endif()
		