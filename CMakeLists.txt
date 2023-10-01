cmake_minimum_required(VERSION 3.5)

project(rtype)

# set the C++ standard to C++ 23
set (CMAKE_CXX_STANDARD 23)

# Inclure le sous-module SFML
add_subdirectory(SFML)

# faire que les hpp se la sfml soit accessible
include_directories(SFML/include)

# thread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# glob recursive of all files in src (hpp and cpp)
file(GLOB_RECURSE SOURCES
     "src/*.hpp"
     "src/*.cpp"
)

foreach (file ${SOURCES})
    set(MYFILE_DIR)
    # print the file name
    message(STATUS "Found file: ${file}")
    if (file MATCHES ".*.hpp")
        get_filename_component(MYFILE_DIR ${file} DIRECTORY)
        include_directories(${MYFILE_DIR})
    endif()
endforeach()

# Votre code source
add_executable(rtype ${SOURCES})

# Lier votre exécutable avec les bibliothèques SFML
target_link_libraries(rtype sfml-graphics sfml-window sfml-system)
target_link_libraries(rtype ${Boost_LIBRARIES})

# Link thread on linux
# target_link_libraries(rtype pthread)

# if debug

if (CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "Debug mode")
    target_compile_definitions(rtype PUBLIC DEBUG)
endif()
