CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
Project(GUI)

# Set Wt include and library paths
INCLUDE_DIRECTORIES("C:/Program Files/Wt 3.3.7 msvs2013 x64/include/")
LINK_DIRECTORIES("C:/Program Files/Wt 3.3.7 msvs2013 x64/lib/")

# If Visual Studio IDE
IF(MSVC_IDE)
	# Copy user file
  FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.vcxproj.user DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
ENDIF(MSVC_IDE)

# If Eclipse IDE
IF(${CMAKE_EXTRA_GENERATOR} MATCHES ".*Eclipse.*")
	IF(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		# Copy debug user file
    FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}-debug.exe.launch DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	ENDIF()
	IF(${CMAKE_BUILD_TYPE} STREQUAL "Release")
		# Copy release user file
    FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}-release.exe.launch DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
	ENDIF()
ENDIF()

# Copy resources to build tree
FILE(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

SET(gui_SRC main.cpp
               gui.cpp)

# If Visual Studio IDE
IF(MSVC_IDE)
	SET(gui_SRC ${gui_SRC} gui.h
		                         ui_gui.h)
ENDIF(MSVC_IDE)

ADD_EXECUTABLE(GUI ${gui_SRC})

TARGET_LINK_LIBRARIES(GUI
  debug wtd.lib optimized wt.lib
  debug wthttpd.lib optimized wthttp.lib
  debug libboost_date_time-vc120-mt-gd-1_63.lib optimized libboost_date_time-vc120-mt-1_63.lib
  debug libboost_filesystem-vc120-mt-gd-1_63.lib optimized libboost_filesystem-vc120-mt-1_63.lib
  debug libboost_program_options-vc120-mt-gd-1_63.lib optimized libboost_program_options-vc120-mt-1_63.lib
  debug libboost_regex-vc120-mt-gd-1_63.lib optimized libboost_regex-vc120-mt-1_63.lib
  debug libboost_signals-vc120-mt-gd-1_63.lib optimized libboost_signals-vc120-mt-1_63.lib
  debug libboost_system-vc120-mt-gd-1_63.lib optimized libboost_system-vc120-mt-1_63.lib
  debug libboost_thread-vc120-mt-gd-1_63.lib optimized libboost_thread-vc120-mt-1_63.lib
  debug libboost_random-vc120-mt-gd-1_63.lib optimized libboost_random-vc120-mt-1_63.lib
  )
