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

add_executable(piratesofold 
  main.cpp 
  gameplay/Pirate.cpp
)
install(TARGETS piratesofold DESTINATION bin)
target_link_libraries(piratesofold ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES})
