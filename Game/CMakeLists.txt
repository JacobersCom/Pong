add_executable(Pong main.cpp)

target_link_libraries(Pong PRIVATE Project)

if(WIN32)
	set (SDL3_DLL "${CMAKE_CURRENT_SOURCE_DIR}/Project/deps/SDL3.dll")
	if(EXISTS "${SDL3_DLL})
		add_custom_command(TARGET Pong POST_BUILD COMMMAND ${CMAKE_COMMAND} 
		-E copy_if_different "${SDL3_DLL}"
		$<TARGET_FILE_DIR:Pong>
		COMMENT "Copying SDL3.dll next to Pong.exe
	)
	endif()
endif()
		