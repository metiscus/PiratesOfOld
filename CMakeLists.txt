project(PiratesOfOld)
cmake_minimum_required(VERSION 2.8)

# Point to our own cmake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

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
)

target_link_libraries(PiratesOfOld ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
