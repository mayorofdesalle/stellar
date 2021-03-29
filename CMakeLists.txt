cmake_minimum_required( VERSION 3.16.3 )
project( ARP87 VERSION 0.1 LANGUAGES CXX )

set( SFML_CMAKE #[[PATH_TO_SFML_CMAKE_FOLDER]])
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_CXX_STANDARD_REQUIRED TRUE )

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug
    CACHE STRING "Choose the type of build (Debug or Release)" FORCE )
endif()

set ( SOURCE_STARMAP ./Starmap/Starmap.cpp )
add_library( STARMAP SHARED ${SOURCE_STARMAP} )

set( SOURCE_EXE ./main.cpp )
add_executable( ${PROJECT_NAME} ${SOURCE_EXE} )

list( APPEND CMAKE_PREFIX_PATH ${SFML_CMAKE} )
find_package( SFML 2.5 COMPONENTS audio network graphics window system REQUIRED )
target_link_libraries( STARMAP PUBLIC sfml-graphics sfml-system )
target_link_libraries( ${PROJECT_NAME} PRIVATE STARMAP )