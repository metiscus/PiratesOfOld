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

add_subdirectory(lua-5.2.3)

# Find SDL2
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

# Add global definitions
add_definitions("-Wall")
include_directories(${SDL2_INCLUDE_DIR})

add_executable(PiratesOfOld 
  main.cpp
  gameplay/Pirate.cpp
  gameplay/Date.cpp
  gameplay/Territory.cpp
  gameplay/Nation.cpp
  gameplay/GameWorld.cpp
  gameplay/Map.cpp
  gameplay/Ship.cpp
  ui/Screen.cpp
)

target_link_libraries(PiratesOfOld ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} lua)
