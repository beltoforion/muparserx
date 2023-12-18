########################################################################
# Project setup
########################################################################
cmake_minimum_required(VERSION 3.17)
project(muparserx CXX)

########################################################################
# Extract version
########################################################################
set(MUPARSERX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/parser)
file(READ "${MUPARSERX_SOURCE_DIR}/mpDefines.h" mpDefines_h)
string(REGEX MATCH "\\#define MUP_PARSER_VERSION _T\\(\"([0-9]+\\.[0-9]+\\.[0-9]+) \\(" MUPARSERX_VERSION_MATCHES "${mpDefines_h}")
if(NOT MUPARSERX_VERSION_MATCHES)
    message(FATAL_ERROR "Failed to extract version number from mpDefines.h")
endif(NOT MUPARSERX_VERSION_MATCHES)
set(MUPARSERX_VERSION ${CMAKE_MATCH_1})

########################################################################
# Compiler specific flags
########################################################################
if(CMAKE_COMPILER_IS_GNUCXX OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    set(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG -g3 -gdwarf-3")
    set(CMAKE_CXX_FLAGS_COVERAGE "-D_DEBUG -g3 -gdwarf-3 --coverage")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

endif(CMAKE_COMPILER_IS_GNUCXX OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang"))

if(MSVC)
    add_compile_options(/MP) #multi-core build
    add_compile_options(/std:c++17)
endif(MSVC)

########################################################################
# Build library
# Defaults to static, set BUILD_SHARED_LIBS=ON for shared
########################################################################
file(GLOB MUPARSERX_SOURCES "${MUPARSERX_SOURCE_DIR}/*.cpp")
include_directories(${MUPARSERX_SOURCE_DIR})
add_library(muparserx ${MUPARSERX_SOURCES})
set_target_properties(muparserx PROPERTIES VERSION ${MUPARSERX_VERSION})
set_property(TARGET muparserx PROPERTY POSITION_INDEPENDENT_CODE TRUE)
set_target_properties(muparserx PROPERTIES SOVERSION ${MUPARSERX_VERSION})
set_target_properties(muparserx PROPERTIES VERSION ${MUPARSERX_VERSION})

#link with lib math when found
find_library(
    M_LIBRARY NAMES m
    PATHS /usr/lib /usr/lib64
)
if(M_LIBRARY)
    target_link_libraries(muparserx ${M_LIBRARY})
endif(M_LIBRARY)

install(TARGETS muparserx
    LIBRARY DESTINATION lib${LIB_SUFFIX} # .so file
    ARCHIVE DESTINATION lib${LIB_SUFFIX} # .lib file
    RUNTIME DESTINATION bin              # .dll file
)

########################################################################
# Build pkg config file
########################################################################
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/muparserx.in.pc
    ${CMAKE_CURRENT_BINARY_DIR}/muparserx.pc
@ONLY)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/muparserx.pc
    DESTINATION lib${LIB_SUFFIX}/pkgconfig
)

########################################################################
# Install project config
########################################################################
configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/muparserxConfigVersion.in.cmake
    ${PROJECT_BINARY_DIR}/muparserxConfigVersion.cmake
@ONLY)
set(cmake_files
    ${PROJECT_SOURCE_DIR}/cmake/muparserxConfig.cmake
    ${PROJECT_BINARY_DIR}/muparserxConfigVersion.cmake)
if (UNIX)
    install(FILES ${cmake_files} DESTINATION share/cmake/muparserx)
elseif (WIN32)
    install(FILES ${cmake_files} DESTINATION cmake)
endif ()

########################################################################
# Install headers
########################################################################
file(GLOB MUPARSERX_HEADERS "${MUPARSERX_SOURCE_DIR}/*.h")
install(
    FILES ${MUPARSERX_HEADERS}
    DESTINATION include/muparserx
)

########################################################################
# Options
########################################################################

option(BUILD_EXAMPLES "enable building example applications" ON)
if(BUILD_EXAMPLES)
    add_executable(example sample/example.cpp sample/timer.cpp)
    target_link_libraries(example muparserx)
endif(BUILD_EXAMPLES)

option(USE_WIDE_STRING "use UNICODE characters" OFF)
if(USE_WIDE_STRING)
    add_compile_definitions(MUP_USE_WIDE_STRING)
endif(USE_WIDE_STRING)

########################################################################
# Print summary
########################################################################

message(STATUS "Building muparserx version: ${MUPARSERX_VERSION}")
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
