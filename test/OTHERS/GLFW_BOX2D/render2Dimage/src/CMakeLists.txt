#--------------------------------------------------------------------------------------------------------
# SAMPLES : http://content.gpwiki.org/File:Blob.zip
#--------------------------------------------------------------------------------------------------------
# PARA COMPILAR SOIL2
# Descargar de https://bitbucket.org/SpartanJ/soil2
# $> premake4 gmail
# $> cd make/macosx
# $> make
# $> sudo cp ../../lib/macosx/libsoil2.a /opt/local/lib
# $> sudo cp -rf src/SOIL2 /opt/local/include/.
#--------------------------------------------------------------------------------------------------------
# PARA COMPILAR BOX2D OSX 10.9.4
# Descargar la version deseada
# Ir a Box2D/Build
# $> cmake -DBOX2D_INSTALL=ON -DBOX2D_INSTALL_DOC=ON -DBOX2D_BUILD_SHARED=ON -DBOX2D_BUILD_STATIC=ON -DBOX2D_BUILD_EXAMPLES=OFF -DCMAKE_INSTALL_PREFIX=/opt/local/ ..
# $> make
# $> sudo make install
#--------------------------------------------------------------------------------------------------------
# PARA COMPILAR GLFW 3 OSX 10.9.4
# $> git clone https://github.com/glfw/glfw.git
# $> cd glfw
# $> mkdir build
# Ahora usamos CCMAKE para configurar las opciones de compilado. Cambiaremos el PREFIX 
# $> ccmake 
# $> make
# $> sudo make install
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
main.hpp
contrib/jsoncpp.cpp
contrib/json.h					
)


IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")	
    MESSAGE( "SISTEMA: Apple OS X" )
    MESSAGE( "==========================================================================" )	
    
    IF(${CMAKE_BUILD_TYPE} MATCHES "Debug")
      add_definitions("-std=c++11 -DAPPLE -O0 -Wall -Wextra -pedantic -W -Wconversion -Wcast-qual -Wwrite-strings -Wstrict-aliasing  -Wpointer-arith -Wcast-align -fno-common") 
    ELSE()
      add_definitions("-std=c++11 -DAPPLE -O3 -Wall -Wextra -pedantic -W -Wconversion -Wcast-qual -Wwrite-strings -Wstrict-aliasing  -Wpointer-arith -Wcast-align -fno-common") 
    ENDIF()

	FIND_PATH(SOIL2_INCLUDE_DIRS SOIL2/SOIL2.h)	  
	FIND_LIBRARY(SOIL2_LIBRARIES NAMES soil2.a libsoil2.a PATHS /opt/local/lib /usr/local/lib)	
	MESSAGE( "SOIL2 include location: " ${SOIL2_INCLUDE_DIRS} )
	MESSAGE( "SOIL2 library location: " ${SOIL2_LIBRARIES} )

	FIND_PATH(GLFW_INCLUDE_DIRS GLFW/glfw3.h)	  
	FIND_LIBRARY(GLFW_LIBRARIES NAMES glfw.a glfw3.a libglfw.a libglfw3.a PATHS /opt/local/lib /usr/local/lib)	
	MESSAGE( "GLFW3 include location: " ${GLFW_INCLUDE_DIRS} )
	MESSAGE( "GLFW3 library location: " ${GLFW_LIBRARIES} )
		
	FIND_PATH(BOX2D_INCLUDE_DIR  Box2D/Box2D.h)	  
	FIND_LIBRARY(BOX2D_LIBRARY NAMES Box2D.a box2d.a Box2d.a box2D.a libBox2D.a libbox2d.a libBox2d.a libbox2D.a PATHS /opt/local/lib /usr/local/lib)		
	MESSAGE( "Box2D include location: " ${BOX2D_LIBRARY} )
	MESSAGE( "Box2D library location: " ${BOX2D_INCLUDE_DIR} )
	
	SET(GUI_TYPE MACOSX_BUNDLE)
	SET(COCOA_FRAMEWORK "-framework Cocoa")
	SET(OpenGL_LIBRARY "-framework OpenGL")
	SET(IOKIT_FRAMEWORK "-framework IOKit")
	SET(COREVIDEO_FRAMEWORK "-framework CoreVideo")
    		
	INCLUDE_DIRECTORIES(${SOIL2_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${BOX2D_INCLUDE_DIR} /System/Library/Frameworks)		
	TARGET_LINK_LIBRARIES(${TARGET} ${SOIL2_LIBRARIES} ${GLFW_LIBRARIES} ${COCOA_FRAMEWORK} ${OpenGL_LIBRARY} ${IOKIT_FRAMEWORK} ${COREVIDEO_FRAMEWORK} ${BOX2D_LIBRARY})
	
ELSE()
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		MESSAGE( "SISTEMA: Linux" )
		MESSAGE( "==========================================================================" )    	           
	ELSE()
		MESSAGE( STATUS "ATENCION ALGO VA MAL !!! -> NO SE HA DETECTADO EL SISTEMA : " ${CMAKE_SYSTEM_NAME})
		MESSAGE( "==========================================================================" )
	ENDIF()
ENDIF()
