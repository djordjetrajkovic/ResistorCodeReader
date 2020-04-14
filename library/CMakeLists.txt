# ./library/CMakeLists.txt

cmake_minimum_required( VERSION 3.17...3.17 )

project( OpenCVLibs
        VERSION 1.0.0
        DESCRIPTION "The internal libraries."
    )

# An library
add_library( classification SHARED )

target_sources( classification 
    PRIVATE "src/classification.cpp"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/classification.h"        
)

target_include_directories( classification PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

target_link_libraries( classification PUBLIC OCV::highgui)
target_link_libraries( classification PUBLIC OCV::imgproc)
target_link_libraries( classification PUBLIC OCV::video)
target_link_libraries( classification PUBLIC OCV::core)

# Create ALIAS targets.
add_library( MyOpenCV::classification ALIAS classification ) 