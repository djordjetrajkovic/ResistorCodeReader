# ./library/CMakeLists.txt

cmake_minimum_required( VERSION 3.16 )

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

target_link_libraries( classification PUBLIC opencv_highgui )
target_link_libraries( classification PUBLIC opencv_imgproc )
target_link_libraries( classification PUBLIC opencv_video   )
target_link_libraries( classification PUBLIC opencv_core    )

# Create ALIAS targets.
add_library( MyOpenCV::classification ALIAS classification ) 