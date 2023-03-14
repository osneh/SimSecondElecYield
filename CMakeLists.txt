# Setup the project
cmake_minimum_required(VERSION 3.16...3.21 FATAL_ERROR)
project(SimSecondElecYield)

# find GEANT4
find_package(Geant4 REQUIRED ui_all vis_all)

# setup Geant4 , include, compile definitions, directories
include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

# add th executable and link it to te Geant4 libraries
add_executable(simSEY simSEY.cc ${sources} ${headers})
target_link_libraries(simSEY ${Geant4_LIBRARIES})

add_custom_target(SimSEY DEPENDS simSEY)
