cmake_minimum_required( VERSION 3.0 )

set( PROJECT_NAME "darwinhelper" )

project( ${PROJECT_NAME} )

message( STATUS "Project: ${PROJECT_NAME}" )
message( STATUS "Project directory: ${PROJECT_SOURCE_DIR}" )

set( SOURCE_DIR "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_DIR "${SOURCE_DIR}/include" )
set( INSTALL_DIR "${CMAKE_INSTALL_PREFIX}" )
set (
    INSTALL_LIB_DIR
    "${INSTALL_DIR}/lib/${PLATFORM}/${TARGET}/${ARCHITECTURE}"
    )

message( STATUS "Source directory: ${SOURCE_DIR}" )
message( STATUS "Include directory: ${INCLUDE_DIR}" )
message( STATUS "Install directory: ${INSTALL_DIR}" )

set( SOURCES "${SOURCE_DIR}/darwin_helper.c" )

set( HEADERS "${INCLUDE_DIR}/darwin_helper.h" )

include_directories( ${INCLUDE_DIR} )

find_path( CORE_FOUNDATION_INCLUDES "CoreFoundation/CoreFoundation.h" )

set( EXTRA_INCLUDES ${CORE_FOUNDATION_INCLUDES} ${CORE_AUDIO_INCLUDES} )

message( STATUS "Framework include directories: ${EXTRA_INCLUDES}" )

include_directories( ${EXTRA_INCLUDES} )

message( STATUS "C source files found: ${SOURCES}" )
message( STATUS "C header files found: ${HEADERS}" )

add_library( ${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS} )

target_link_libraries( ${PROJECT_NAME} cpcommon )

set( CPCOMMON_INCLUDE_DIR "${cpcommon_SOURCE_DIR}/src/include" )

message (
  STATUS
  "Working with cpcommon source directory: ${CPCOMMON_INCLUDE_DIR}"
        )

include_directories( ${CPCOMMON_INCLUDE_DIR} )

install (
          TARGETS ${PROJECT_NAME}
          ARCHIVE DESTINATION "${INSTALL_LIB_DIR}"
          LIBRARY DESTINATION "${INSTALL_LIB_DIR}"
        )
install( FILES ${HEADERS} DESTINATION "${INSTALL_DIR}/include/${PROJECT_NAME}" )

find_library( CORE_FOUNDATION_FRAMEWORK CoreFoundation )

set( EXTRA_LIBS ${CORE_FOUNDATION_FRAMEWORK} )

message( STATUS "Framework libraries: ${EXTRA_LIBS}" )

target_link_libraries( ${PROJECT_NAME} ${EXTRA_LIBS} )

find_package( Doxygen )

if( DOXYGEN_FOUND )
  set( DOXYGEN_OUTPUT "${INSTALL_DIR}/doc/${PROJECT_NAME}" )

  configure_file  (
    ${PROJECT_SOURCE_DIR}/Doxyfile.in
    ${PROJECT_BINARY_DIR}/Doxyfile
    @ONLY
                  )
  add_custom_target (
    doc_darwinhelper
    ${DOXYGEN_EXECUTABLE} ${PROJECT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
                    )

  file( MAKE_DIRECTORY ${DOXYGEN_OUTPUT} )

endif(DOXYGEN_FOUND)
