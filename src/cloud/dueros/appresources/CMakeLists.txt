cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(APPRESOURCES LANGUAGES CXX)

include(../build/BuildDefaults.cmake)

install(DIRECTORY 
    "${PROJECT_SOURCE_DIR}"
    DESTINATION
    "${CMAKE_INSTALL_PREFIX}"
    FILES_MATCHING PATTERN "*.mp3")

install(DIRECTORY 
    "${PROJECT_SOURCE_DIR}"
    DESTINATION
    "${CMAKE_INSTALL_PREFIX}"
    FILES_MATCHING PATTERN "*.wav")

install(DIRECTORY 
    "${PROJECT_SOURCE_DIR}"
    DESTINATION
    "${CMAKE_INSTALL_PREFIX}"
    FILES_MATCHING PATTERN "*.pcm")

