#--------------------------------------------------------------------------------------------------------
# PARA COMPILAR BOX2D
# Descargar la version deseada
# Ir a Box2D/Build
# $> cmake -DBOX2D_INSTALL=ON -DBOX2D_INSTALL_DOC=ON -DBOX2D_BUILD_SHARED=ON -DBOX2D_BUILD_STATIC=ON -DBOX2D_BUILD_EXAMPLES=OFF -DCMAKE_INSTALL_PREFIX=/opt/local/ ..
# $> make
# $> make install
#--------------------------------------------------------------------------------------------------------
# VARIANTES PARA COMPILAR EL PROYECTO
# cmake -DCMAKE_BUILD_TYPE=Debug -G Xcode ../../../src
# cmake -DCMAKE_BUILD_TYPE=Release -G Xcode ../../../src
# cmake --debug-output -DCMAKE_BUILD_TYPE=Debug ../../../src
#--------------------------------------------------------------------------------------------------------
#  !!!!! USAR SIMPRE CON EJECUTABLES DES-OPTIMIZADOS -O0 !!!!!!
#  valgrind -v --num-callers=20 --leak-check=yes --leak-resolution=high --show-reachable=yes ./ejecutable
#--------------------------------------------------------------------------------------------------------

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
	
	PKG_SEARCH_MODULE(SDL REQUIRED sdl)
	PKG_SEARCH_MODULE(SDLIMAGE REQUIRED SDL_image)		
	MESSAGE( "SDL include location: " ${SDL_INCLUDE_DIRS} )
	MESSAGE( "SDL library location: " ${SDL_LIBRARIES} )
	MESSAGE( "SDL Image include location: " ${SDLIMAGE_INCLUDE_DIRS} )
	MESSAGE( "SDL Image library location: " ${SDLIMAGE_LIBRARIES} )
	
	
	
	FIND_PATH(BOX2D_INCLUDE_DIR  Box2D/Box2D.h)	  
	FIND_LIBRARY(BOX2D_LIBRARY NAMES Box2D.a box2d.a Box2d.a box2D.a libBox2D.a libbox2d.a libBox2d.a libbox2D.a PATHS /opt/local/lib /usr/local/lib)		
	MESSAGE( "Box2D include location: " ${BOX2D_LIBRARY} )
	MESSAGE( "Box2D library location: " ${BOX2D_INCLUDE_DIR} )
	
	SET(GUI_TYPE MACOSX_BUNDLE)
	SET(COCOA_FRAMEWORK "-framework Cocoa")
	SET(OpenGL_LIBRARY "-framework OpenGL")
	SET(IOKIT_FRAMEWORK "-framework IOKit")
	SET(COREVIDEO_FRAMEWORK "-framework CoreVideo")
    		
	INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${BOX2D_INCLUDE_DIR} /System/Library/Frameworks)		
	TARGET_LINK_LIBRARIES(${TARGET} ${SDL_LIBRARIES} ${SDLIMAGE_LIBRARIES} ${GLFW_LIBRARIES} ${COCOA_FRAMEWORK} ${OpenGL_LIBRARY} ${IOKIT_FRAMEWORK} ${COREVIDEO_FRAMEWORK} ${BOX2D_LIBRARY})
	
	
	


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
