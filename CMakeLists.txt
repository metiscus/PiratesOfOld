cmake_minimum_required(VERSION 2.8)
project(PiratesOfOld)

# Check for c++11 features
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
#end of c++11 

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lua-5.2.3/src)

add_subdirectory(lua-5.2.3)
add_subdirectory(angelscript-2.29.2/sdk/angelscript/projects/cmake)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Add global definitions
add_definitions("-Wall -Wextra")
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_PATH})
include_directories(glm)
include_directories(angelscript-2.29.2/sdk/angelscript/include)
include_directories(angelscript-2.29.2/sdk)

add_executable(PiratesOfOld 
  main.cpp
  engine/EventListener.cpp
  engine/EventManager.cpp
  engine/Game.cpp
  engine/Renderer.cpp
  engine/ResourceLoader.cpp
  engine/Screen.cpp
  engine/ScreenElement.cpp
  engine/ScreenManager.cpp
  engine/Scriptable.cpp
  engine/ScriptEnvironment.cpp
  engine/Window.cpp
  engine/stb/stb_truetype.cpp
  engine/stb/stb_image.cpp
  gameplay/Pirate.cpp
  gameplay/Date.cpp
  gameplay/Territory.cpp
  gameplay/Nation.cpp
  gameplay/GameWorld.cpp
  gameplay/Map.cpp
  gameplay/Ship.cpp
  engine/Model.cpp
  engine/Controller.cpp
  src/WorldMapModel.cpp
  src/WorldMapView.cpp
  src/WorldMapController.cpp
)

configure_file(data/default.frag ${CMAKE_CURRENT_BINARY_DIR}/data/default.frag COPYONLY)
configure_file(data/default.vert ${CMAKE_CURRENT_BINARY_DIR}/data/default.vert COPYONLY)
configure_file(data/DroidSans.ttf ${CMAKE_CURRENT_BINARY_DIR}/data/DroidSans.ttf COPYONLY)
configure_file(data/scripts/main.lua ${CMAKE_CURRENT_BINARY_DIR}/data/scripts/main.lua COPYONLY)

## This requires sdl2_ttf library from https://www.libsdl.org/projects/SDL_ttf/
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lGLEW")

target_link_libraries(PiratesOfOld ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} lua Angelscript)
