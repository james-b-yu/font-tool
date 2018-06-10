cmake_minimum_required(VERSION 2.6)
project(FontTool)

set(CMAKE_CXX_FLAGS_DEBUG "-MTd /ZI -MP -fp:fast -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -DCURL_STATICLIB -DBOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE -D_CRTDBG_MAP_ALLOC")

set(CMAKE_CXX_FLAGS_RELEASE "-O1 -Os -MT -MP -fp:fast -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -DCURL_STATICLIB -DBOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE -DNDEBUG -D_NDEBUG_ -DwxDEBUG_LEVEL=0")

if (CMAKE_BULD_TYPE STREQUAL Release)
set(wxWidgets_CONFIGURATION mswu)
else()
set(wxWidgets_CONFIGURATION mswud)
endif()

find_package(wxWidgets COMPONENTS base core adv html xml richtext REQUIRED)
include(${wxWidgets_USE_FILE})

file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/src/*.h)
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
include_directories(${CMAKE_SOURCE_DIR})

link_libraries(debug libcurl_a_debug.lib)
link_libraries(optimized libcurl_a.lib)

link_libraries(FontTool ${wxWidgets_LIBRARIES})

# setting the language
OPTION(LANG "Setting the language" 0) # Enabled by default
ADD_DEFINITIONS(-DLANG=${LANG})

add_executable(FontTool ${HEADERS} ${SOURCES} ${CMAKE_SOURCE_DIR}/src/resource.rc)
set_target_properties(FontTool PROPERTIES LINK_FLAGS_RELEASE "-SUBSYSTEM:WINDOWS -NXCOMPAT -DYNAMICBASE -LTCG")
