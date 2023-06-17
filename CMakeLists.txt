cmake_minimum_required(VERSION 3.16)
project(ENCRYPTION LANGUAGES C CXX)

#setting standard liberary, C and C+++
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# enabling the unit tests
enable_testing()

# Copy the dependent files of the project (cfg files or files users want to open)
configure_file(${CMAKE_SOURCE_DIR}/.privacy/.encryptionAES256GCM.bin ${CMAKE_BINARY_DIR}/.privacy/.encryptionAES256GCM.bin COPYONLY)

# add the files into the library
add_library(Mains
    Entry.c
)

# Specifying to the headers
target_include_directories(Mains PUBLIC ../../Headers)

# Opening the subdirectory for the next works
add_subdirectory(Sources)
add_subdirectory(tests)