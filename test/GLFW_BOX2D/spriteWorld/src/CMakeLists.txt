#--------------------------------------------------------------------------------------------------------
# SAMPLES : http://content.gpwiki.org/File:Blob.zip
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
DebugDraw.cpp
DebugDraw.h
RenderGL3.cpp
RenderGL3.h
main.cpp
main.hpp
stb_truetype.h
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

	FIND_PATH(GLFW_INCLUDE_DIRS glfw3.h "/opt/local/include/GLFW")	  
	FIND_LIBRARY(GLFW_LIBRARIES NAMES glfw libglfw PATHS /opt/local/lib)
		
	FIND_PATH(BOX2D_INCLUDE_DIR  Box2D/Box2D.h)	  
	FIND_LIBRARY(BOX2D_LIBRARY NAMES Box2D libBox2D PATHS /opt/local/lib)		
	
	
	SET(GUI_TYPE MACOSX_BUNDLE)
	SET(COCOA_FRAMEWORK "-framework Cocoa")
	SET(OpenGL_LIBRARY "-framework OpenGL")
	SET(IOKIT_FRAMEWORK "-framework IOKit")
	SET(COREVIDEO_FRAMEWORK "-framework CoreVideo")
    		
	INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIRS} ${BOX2D_INCLUDE_DIR} /System/Library/Frameworks)		
	TARGET_LINK_LIBRARIES(${TARGET} ${GLFW_LIBRARIES} ${COCOA_FRAMEWORK} ${OpenGL_LIBRARY} ${IOKIT_FRAMEWORK} ${COREVIDEO_FRAMEWORK} ${BOX2D_LIBRARY})
	
ELSE()
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		MESSAGE( "SISTEMA: Linux" )
		MESSAGE( "==========================================================================" )    	           
	ELSE()
		MESSAGE( STATUS "ATENCION ALGO VA MAL !!! -> NO SE HA DETECTADO EL SISTEMA : " ${CMAKE_SYSTEM_NAME})
		MESSAGE( "==========================================================================" )
	ENDIF()
ENDIF()
