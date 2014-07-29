#  cmake -DCMAKE_BUILD_TYPE=Debug ../../"El Barrio es lo Primero"/.
#  cmake -DCMAKE_BUILD_TYPE=Release ../../"El Barrio es lo Primero"/.
#  cmake -DCMAKE_BUILD_TYPE=Debug -G Xcode ../../"El Barrio es lo Primero"/.
#  cmake -DCMAKE_BUILD_TYPE=Release -G Xcode ../../"El Barrio es lo Primero"/.

#  !!!!! USAR SIMPRE CON EJECUTABLES DES-OPTIMIZADOS -O0 !!!!!!
#  valgrind -v --num-callers=20 --leak-check=yes --leak-resolution=high --show-reachable=yes ./ejecutable

SET(CMAKE_LEGACY_CYGWIN_WIN32 0)

project(EL_BARRIO_ES_LO_PRIMERO)
cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR )

SET(TARGET "ElBarrioEsLoPrimero")
 
MESSAGE( "SCAN DE SISTEMA" )
MESSAGE( "==========================================================================" )
MESSAGE( STATUS "SISTEMA ACTUAL              : " ${CMAKE_SYSTEM_NAME} )
MESSAGE( STATUS "MODO                        : " ${CMAKE_BUILD_TYPE} )
MESSAGE( STATUS "CMAKE_COMPILER_IS_GNUCXX    : " ${CMAKE_COMPILER_IS_GNUCXX} )
MESSAGE( STATUS "UNIX                        : " ${UNIX} )
MESSAGE( STATUS "WIN32                       : " ${WIN32} )
MESSAGE( STATUS "APPLE                       : " ${APPLE} )
MESSAGE( STATUS "MINGW                       : " ${MINGW} )
MESSAGE( STATUS "MSYS                        : " ${MSYS} )
MESSAGE( STATUS "CYGWIN                      : " ${CYGWIN} )
MESSAGE( STATUS "BORLAND                     : " ${BORLAND} )
MESSAGE( STATUS "WATCOM                      : " ${WATCOM} )
MESSAGE( "==========================================================================" )

add_executable(${TARGET} 
				main.cpp
				main.hpp					
				)


IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")	
    MESSAGE( "SISTEMA: Apple OS X" )
    MESSAGE( "==========================================================================" )	
    IF(${CMAKE_BUILD_TYPE} MATCHES "Debug")
      add_definitions("-std=c++11 -DAPPLE -O0 -Wall -Wextra -pedantic -W -Wconversion -Wcast-qual -Wwrite-strings -Wstrict-aliasing  -Wpointer-arith -Wcast-align -fno-common") 
    ELSE()
      add_definitions("-std=c++11 -DAPPLE -O3 -Wall -Wextra -pedantic -W -Wconversion -Wcast-qual -Wwrite-strings -Wstrict-aliasing  -Wpointer-arith -Wcast-align -fno-common") 
    ENDIF()

	INCLUDE(FindPkgConfig)
	
	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
	PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
		
	INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})	
	
	TARGET_LINK_LIBRARIES(${TARGET} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
	
	
    #Find_Package ( SDL2 REQUIRED )
    #FIND_PATH(LIBSDL_IMAGE_INCLUDE SDL_image.h "/usr/local/include/SDL2")	  
	#FIND_LIBRARY(LIBSDL_IMAGE_LIBRARY NAMES SDL2_image libSDL2_image PATHS /usr/local/lib)
	#Find_Package ( SDL2_image REQUIRED ) 
	#Find_Package ( SDL2_ttf REQUIRED )
	#Find_Package ( SDL2_mixer REQUIRED )

	#IF ( NOT SDL_FOUND )
	#	MESSAGE ( FATAL_ERROR "Librerias SDL no encontradas. Son dependencias obligatorias(SDL, Image, Mixer, TTF)" )
	#ENDIF( NOT SDL_FOUND )
	#target_link_libraries ( ${TARGET} ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY} ${SDLMIXER_LIBRARY})
	#include_directories ( ${LIBSDL_IMAGE_INCLUDE})
	#target_link_libraries ( ${TARGET} ${SDL_LIBRARY} ${LIBSDL_IMAGE_LIBRARY})

ELSE()
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		MESSAGE( "SISTEMA: Linux" )
		MESSAGE( "==========================================================================" )
           
		IF(${CMAKE_BUILD_TYPE} MATCHES "Debug")
			add_definitions("-std=c++11 -DLINUX -O0 -Wall -Wextra -pedantic -W -Wconversion -Wcast-qual -Wwrite-strings -Wstrict-aliasing  -Wpointer-arith -Wcast-align -fno-common") 
		ELSE()
			add_definitions("-std=c++11 -DLINUX -O3 -Wall -Wextra -pedantic -W -Wconversion -Wcast-qual -Wwrite-strings -Wstrict-aliasing  -Wpointer-arith -Wcast-align -fno-common") 
		ENDIF()
		Find_Package ( SDL REQUIRED )
		Find_Package ( SDL_image REQUIRED ) 
		#Find_Package ( SDL_ttf REQUIRED )
		#Find_Package ( SDL_mixer REQUIRED )
		IF ( NOT SDL_FOUND )
			MESSAGE ( FATAL_ERROR "Librerias SDL no encontradas. Son dependencias obligatorias(SDL, Image, Mixer, TTF)" )
		ENDIF( NOT SDL_FOUND )
		target_link_libraries ( ${TARGET} ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLTTF_LIBRARY} ${SDLMIXER_LIBRARY})              
	ELSE()
		MESSAGE( STATUS "ATENCION ALGO VA MAL !!! -> NO SE HA DETECTADO EL SISTEMA : " ${CMAKE_SYSTEM_NAME})
		MESSAGE( "==========================================================================" )
	ENDIF()
ENDIF()
