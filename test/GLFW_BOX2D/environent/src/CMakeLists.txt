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

	INCLUDE(FindPkgConfig)
	
	PKG_SEARCH_MODULE(GLFW REQUIRED glfw3)
		
	FIND_PATH(BOX2D_INCLUDE_DIR Box2D.h "/usr/local/include/Box2D")	  
	FIND_LIBRARY(BOX2D_LIBRARY NAMES Box2D libBox2D PATHS /usr/local/lib)	
	

    option(GLFW_BUILD_UNIVERSAL "Build the GLFW library and examples as Universal Binaries" FALSE)

    # Universal build
    if (GLFW_BUILD_UNIVERSAL)
        message(STATUS "Building GLFW as Universal Binaries")
        set(CMAKE_OSX_ARCHITECTURES ppc;i386;ppc64;x86_64)
        set(CMAKE_OSX_SYSROOT /Developer/SDKs/MacOSX10.5.sdk)
        set(CMAKE_C_FLAGS "-mmacosx-version-min=10.5") 
    else(GLFW_BUILD_UNIVERSAL)
        message(STATUS "Building GLFW only for the native architecture")
    endif(GLFW_BUILD_UNIVERSAL)
	
    SET(GUI_TYPE MACOSX_BUNDLE)
    INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)       
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL)   
    FIND_LIBRARY(IOKIT_FRAMEWORK IOKit)
    FIND_LIBRARY(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    MARK_AS_ADVANCED(COCOA_LIBRARY OpenGL_LIBRARY)
    		
	INCLUDE_DIRECTORIES(${GLFW_INCLUDE_DIRS} ${BOX2D_INCLUDE_DIR})		
	TARGET_LINK_LIBRARIES(${TARGET} ${CORE_FOUNDATION_FRAMEWORK} ${COCOA_FRAMEWORK} ${IOKIT_FRAMEWORK} ${OpenGL_LIBRARY}brew tap homebrew/versions ${GLFW_LIBRARIES} ${BOX2D_LIBRARY})
	
ELSE()
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
		MESSAGE( "SISTEMA: Linux" )
		MESSAGE( "==========================================================================" )    	           
	ELSE()
		MESSAGE( STATUS "ATENCION ALGO VA MAL !!! -> NO SE HA DETECTADO EL SISTEMA : " ${CMAKE_SYSTEM_NAME})
		MESSAGE( "==========================================================================" )
	ENDIF()
ENDIF()
