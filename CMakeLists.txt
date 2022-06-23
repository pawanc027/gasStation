cmake_minimum_required(VERSION 3.10)

# set the project name
project(myGasStation)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify Flags
set(CMAKE_CXX_FLAGS "-Wall")

# Add the executable
add_executable(myGasStation src/gasStation.cpp)

# I../includes
include_directories(inc)

target_link_libraries(myGasStation pthread)

install(TARGETS myGasStation DESTINATION bin)

set_target_properties( myGasStation
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
