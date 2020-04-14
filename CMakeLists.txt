#./CMakeLists.txt

cmake_minimum_required( VERSION 3.15..3.17 )

project( OpenCV_Project_Framework
        VERSION 1.0
        DESCRIPTION "Tree structure for OpenCV project using CMake."
        )

set( CMAKE_POSITION_INDEPENDENT_CODE ON )

# Make external libraries globally available
add_subdirectory( external )

# Create targets for building the (local) libraries
add_subdirectory( library )

# Create the targets for the entire example
add_subdirectory( app )