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
Camera.cpp
Camera.hpp
Character.cpp
Character.hpp
Clip.hpp
CollisionListener.cpp
CollisionListener.hpp
Colors.hpp
Controller.cpp
Controller.hpp
Conv.hpp
Entities.hpp
ErrorsCodes.hpp
Fixture.hpp
Flags.hpp
FrameRate.hpp
Furnitures.cpp
Furnitures.hpp
Game.cpp
Game.hpp
Glob.hpp
LTimer.cpp
LTimer.hpp
Level.cpp
Level.hpp
Level_1.cpp
Level_1.hpp
LevelsFactory.hpp
Measures.hpp
Names.hpp
Object.hpp
Physics.cpp
Physics.hpp
Render.cpp
Render.hpp
Size.hpp
Sprite.cpp
Sprite.hpp
Text.cpp
Text.hpp
Texture.cpp
Texture.hpp
main.cpp
main.hpp
contrib/jsoncpp.cpp
contrib/json.h)

source_group("utilities" FILES Conv.hpp Fixture.hpp LTimer.cpp LTimer.hpp FrameRate.hpp)
source_group("constants" FILES ErrorsCodes.hpp Colors.hpp Entities.hpp Flags.hpp Measures.hpp Names.hpp)
source_group("types" FILES Size.hpp Clip.hpp Object.hpp Glob.hpp)
source_group("sprites" FILES Texture.cpp Texture.hpp Sprite.hpp Sprite.cpp Character.cpp Character.hpp Furnitures.cpp Furnitures.hpp Text.hpp Text.cpp)
source_group("physics" FILES Physics.hpp Physics.cpp CollisionListener.hpp CollisionListener.cpp)
source_group("render" FILES Render.hpp Render.cpp Camera.hpp Camera.cpp)
source_group("controller" FILES Controller.cpp Controller.hpp)
source_group("contrib" FILES contrib/jsoncpp.cpp contrib/json.h)
source_group("levels" FILES Level.cpp Level.hpp Level_1.hpp Level_1.cpp LevelsFactory.hpp)
source_group("main" FILES main.cpp main.hpp Game.cpp Game.hpp)


IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")	
    MESSAGE( "SISTEMA: Apple OS X" )
    MESSAGE( "==========================================================================" )	
    IF(${CMAKE_BUILD_TYPE} MATCHES "Debug")
      add_definitions("-std=c++11 -DAPPLE -O0 -Wall -Wextra -pedantic -W -Wconversion -Wcast-qual -Wwrite-strings -Wstrict-aliasing  -Wpointer-arith -Wcast-align -fno-common") 
    ELSE()
      add_definitions("-std=c++11 -DAPPLE -O3 -Wall -Wextra -pedantic -W -Wconversion -Wcast-qual -Wwrite-strings -Wstrict-aliasing  -Wpointer-arith -Wcast-align -fno-common") 
    ENDIF()

	# Variables de entorno para Xcode
	set(HEADER_SEARCH_PATHS "/usr/local/include" "/opt/local/include")
	set(LIBRARY_SEARCH_PATHS "/usr/local/lib" "/opt/local/lib")


	INCLUDE(FindPkgConfig)
	
	PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
	PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
	PKG_SEARCH_MODULE(SDL2MIXER REQUIRED SDL2_mixer>=2.0.0)
	PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.0)	
	
	FIND_PATH(BOX2D_INCLUDE_DIR  Box2D/Box2D.h)	  
	FIND_LIBRARY(BOX2D_LIBRARY NAMES Box2D.a box2d.a Box2d.a box2D.a libBox2D.a libbox2d.a libBox2d.a libbox2D.a PATHS /opt/local/lib /usr/local/lib)		
	MESSAGE( "Box2D include location: " ${BOX2D_LIBRARY} )
	MESSAGE( "Box2D library location: " ${BOX2D_INCLUDE_DIR} )
	
	FIND_PATH(SDL2GFX_INCLUDE_DIRS SDL2_rotozoom.h "/usr/local/include/SDL2")	  
	FIND_LIBRARY(SDL2GFX_LIBRARIES NAMES SDL2_gfx libSDL2_gfx PATHS /usr/local/lib) 
			
	INCLUDE_DIRECTORIES(${HEADER_SEARCH_PATHS} ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2MIXER_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2GFX_INCLUDE_DIRS} ${BOX2D_INCLUDE_DIR})	
	
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
