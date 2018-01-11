# Project definition
cmake_minimum_required(VERSION 2.6)
project(OpenGL)
SET(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(
	${PROJECT_SOURCE_DIR}/libraries/sql/include
	${PROJECT_SOURCE_DIR}/libraries/json/include
	${PROJECT_SOURCE_DIR}/libraries/curl/include
)

link_directories(
	${PROJECT_SOURCE_DIR}/libraries/curl/lib
	${PROJECT_SOURCE_DIR}/libraries/json/lib
	${PROJECT_SOURCE_DIR}/libraries/sql/lib
)

add_executable(techdemo
	source/main.cpp
	source/SteamApi.cpp
	source/MySQL.cpp
	source/Statement.cpp
	source/Table.cpp
	source/Application.cpp
)

if(WIN32)
  target_link_libraries(techdemo libcurl_imp jsoncpp mariadb) 
ELSE()
  target_link_libraries(techdemo libcurl libjsoncpp mariadb) 
ENDIF()







