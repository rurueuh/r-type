cmake_minimum_required(VERSION 3.5)

project(rtype)

# set the C++ standard to C++ 23
set(CMAKE_CXX_STANDARD 23)
# Inclure le sous-module SFML
set(SFML_STATIC TRUE)
set(BUILD_SHARED_LIBS FALSE)
add_subdirectory(SFML)

add_subdirectory(snappy)

# faire que les hpp se la sfml soit accessibles
include_directories(SFML/include)
include_directories(snappy)

# thread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# glob recursive of all files in src (hpp and cpp)
file(GLOB_RECURSE SOURCES
    "src/*.hpp"
    "src/*.cpp"
)

foreach(file ${SOURCES})
    set(MYFILE_DIR)
    # print the file name
    message(STATUS "Found file: ${file}")
    if(file MATCHES ".*.hpp")
        get_filename_component(MYFILE_DIR ${file} DIRECTORY)
        include_directories(${MYFILE_DIR})
    endif()
endforeach()

# Votre code source pour rtype_client
add_executable(rtype_client ${SOURCES})

# Lier votre exécutable avec les bibliothèques SFML
target_link_libraries(rtype_client sfml-graphics sfml-window sfml-system sfml-network sfml-audio)
target_link_libraries(rtype_client snappy)

# Link thread on Linux
# target_link_libraries(rtype_client pthread)

# if debug
if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Debug mode for rtype_client")
    target_compile_definitions(rtype_client PUBLIC DEBUG)
endif()

# Votre code source pour rtype_server
add_executable(rtype_server ${SOURCES})

# Définir la macro SERVER pour rtype_server
target_compile_definitions(rtype_server PUBLIC SERVER=1)

# Lier votre exécutable avec les bibliothèques SFML
target_link_libraries(rtype_server sfml-network)
target_link_libraries(rtype_server snappy)

# Link thread on Linux
# target_link_libraries(rtype_server pthread)

# if debug
if(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Debug mode for rtype_server")
    target_compile_definitions(rtype_server PUBLIC DEBUG)
endif()
