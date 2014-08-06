# cmake -DCMAKE_BUILD_TYPE=Debug -G Xcode ../../../src
# cmake -DCMAKE_BUILD_TYPE=Release -G Xcode ../../../src
# cmake --debug-output -DCMAKE_BUILD_TYPE=Debug ../../../src

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
Animation.hpp
Camera.cpp
Camera.hpp
Character.cpp
Character.hpp
Colors.hpp
Constants.hpp
DebugInfo.cpp
DebugInfo.hpp
Game.cpp
Game.hpp
Physics.cpp
Physics.hpp
Sprite.cpp
Sprite.hpp
Texture.cpp
Texture.hpp
errorsCodes.hpp
main.cpp
main.hpp	
contrib/jsoncpp.cpp
contrib/json.h)


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
	PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
	PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)	
	
	FIND_PATH(BOX2D_INCLUDE_DIR Box2D.h "/usr/local/include/Box2D")	  
	FIND_LIBRARY(BOX2D_LIBRARY NAMES Box2D libBox2D PATHS /usr/local/lib)
	
	FIND_PATH(SDL2GFX_INCLUDE_DIRS SDL2_rotozoom.h "/usr/local/include/SDL2")	  
	FIND_LIBRARY(SDL2GFX_LIBRARIES NAMES SDL2_gfx libSDL2_gfx PATHS /usr/local/lib) 
			
	INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2GFX_INCLUDE_DIRS} ${BOX2D_INCLUDE_DIR})	
	
	TARGET_LINK_LIBRARIES(${TARGET} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2MIXER_LIBRARIES} ${SDL2TTF_LIBRARIES} ${SDL2GFX_LIBRARIES} ${BOX2D_LIBRARY})
	


ELSE()
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		MESSAGE( "SISTEMA: Linux" )
		MESSAGE( "==========================================================================" )
        MESSAGE( "NO HAY CMAKE PARA LINUX" )   
		             
	ELSE()
		MESSAGE( STATUS "ATENCION ALGO VA MAL !!! -> NO SE HA DETECTADO EL SISTEMA : " ${CMAKE_SYSTEM_NAME})
		MESSAGE( "==========================================================================" )
	ENDIF()
ENDIF()
