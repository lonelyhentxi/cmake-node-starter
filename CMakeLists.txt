cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project(cmake_node_starter)

# start detect vcpkg (optional)
# If at local, this variable will can be set in CMakeSettings.json or at compile-time
# else please leave it empty, then it will search environment variable to find vcpkg toolchain file 
#if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
#	set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_HOME}/scripts/buildsystems/vcpkg.cmake")
#endif()
# end detect vcpkg (optional)

# detect node
# get home path
if (WIN32)
    set(HOME "$ENV{UserProfile}")
else ()
    set(HOME "$ENV{HOME}")
endif ()
# get node version and system arch info
execute_process(COMMAND node --version OUTPUT_VARIABLE NODE_VERSION)
string(REGEX REPLACE "^[vV]" "" NODE_VERSION ${NODE_VERSION})
string(REPLACE "\n" "" NODE_VERSION ${NODE_VERSION})
string(REPLACE "\"" "" NODE_VERSION ${NODE_VERSION})
execute_process(COMMAND node -p "process.arch" OUTPUT_VARIABLE NODE_ARCH)
string(REPLACE "\n" "" NODE_ARCH ${NODE_ARCH})
string(REPLACE "\"" "" NODE_ARCH ${NODE_ARCH})
# get node-gyp path
if (DEFINED ENV{NODE_GYP_HOME})
    set(NODE_GYP_HOME "$ENV{NODE_GYP_HOME}")
else ()
    set(NODE_GYP_HOME "${HOME}/.node-gyp")
endif ()
if (NOT EXISTS ${NODE_GYP_HOME})
    execute_process(COMMAND node-gyp install --devdir "${NODE_GYP_HOME}" OUTPUT_VARIABLE NODE_VERSION)
endif ()
set(NODE_INCLUDE_PATH "${NODE_GYP_HOME}/${NODE_VERSION}/include")
set(NODE_LIBRARIES "${NODE_GYP_HOME}/${NODE_VERSION}/${NODE_ARCH}/node${CMAKE_STATIC_LIBRARY_SUFFIX}")
# end detect node

# start detect N-API
execute_process(COMMAND node -p "require('node-addon-api').include"
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE NODE_ADDON_API_INCLUDE_PATH)
string(REPLACE "\n" "" NODE_ADDON_API_INCLUDE_PATH ${NODE_ADDON_API_INCLUDE_PATH})
string(REPLACE "\"" "" NODE_ADDON_API_INCLUDE_PATH ${NODE_ADDON_API_INCLUDE_PATH})
message(STATUS ${NODE_ADDON_API_INCLUDE_PATH})
# end detect N-API

file(GLOB_RECURSE SOURCE_FILES src/*.hpp src/*.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")

target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_INCLUDE_PATH} ${NODE_ADDON_API_INCLUDE_PATH})
target_link_libraries(${PROJECT_NAME} PRIVATE ${NODE_LIBRARIES})

#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
#find_package(MPI REQUIRED)
#include_directories(includes ${MPI_INCLUDE_PATH})
#target_link_libraries(${PROJECT_NAME} ${MPI_LIBRARIES})