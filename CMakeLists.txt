cmake_minimum_required(VERSION 2.8.11)
project(irecorder)

set(irecorder_VERSION_MAJOR 1)
set(irecorder_VERSION_MINOR 0)

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(QT5_WIDGETS REQUIRED Qt5Widgets)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Widgets)
find_package(Qt5Multimedia)
find_package(Qt5LinguistTools)

include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

configure_file(${PROJECT_SOURCE_DIR}/config.h.in ${PROJECT_BINARY_DIR}/config.h)

file(GLOB SRCS "${PROJECT_SOURCE_DIR}/*.cpp")
set(srcs ${SRCS})
set(target irecorder)

file(GLOB TS ${CMAKE_SOURCE_DIR}/translations/*.ts)
#file(GLOB QM ${CMAKE_SOURCE_DIR}/translations/*.qm)
qt5_create_translation(QM ${SRCS} ${TS})

if (APPLE)
    add_executable(${target} MACOSX_BUNDLE ${srcs} ${QM})
else ()
    add_executable(${target} ${srcs} ${QM})
endif()

target_link_libraries(${target} Qt5::Widgets Qt5::Multimedia)

set(IRECORDER_INSTALL_DATA_DIR share/irecorder/)
install(TARGETS ${target} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(FILES ${QM} DESTINATION
    "${CMAKE_INSTALL_PREFIX}/${IRECORDER_INSTALL_DATA_DIR}")
install(FILES irecorder.png DESTINATION
    "${CMAKE_INSTALL_PREFIX}/share/icons")
install(FILES irecorder.desktop DESTINATION
    "${CMAKE_INSTALL_PREFIX}/share/applications/")
