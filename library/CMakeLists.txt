# ./library/CMakeLists.txt

cmake_minimum_required( VERSION 3.16 )

project( OpenCVLibs
        VERSION 1.0.0
        DESCRIPTION "The internal libraries."
    )

# Find Packege
find_package(OpenCV 4.4)

# An objects library
add_library( objects SHARED )

target_sources( objects 
    PRIVATE "src/objects.cpp"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/object.h"        
)


target_include_directories( objects PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

target_link_libraries( objects PUBLIC opencv_highgui )
target_link_libraries( objects PUBLIC opencv_imgproc )
target_link_libraries( objects PUBLIC opencv_video   )
target_link_libraries( objects PUBLIC opencv_core    )

# An test library
add_library( test SHARED )

target_sources( test 
    PRIVATE "src/access.cpp"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/access.h"        
)
target_include_directories( test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

target_link_libraries( test PUBLIC opencv_highgui )
target_link_libraries( test PUBLIC opencv_imgproc )
target_link_libraries( test PUBLIC opencv_video   )
target_link_libraries( test PUBLIC opencv_core    )
target_link_libraries( test PUBLIC objects        )
target_link_libraries( test PUBLIC opencv_shape   )

# An input library
add_library( input SHARED )

target_sources( input 
    PRIVATE "src/input.cpp"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/input.h"        
)
target_include_directories( input PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

target_link_libraries( input PUBLIC opencv_highgui )
target_link_libraries( input PUBLIC opencv_imgproc )
target_link_libraries( input PUBLIC opencv_video   )
target_link_libraries( input PUBLIC opencv_core    )
target_link_libraries( input PUBLIC objects        )
target_link_libraries( input PUBLIC test           )


# Create ALIAS targets.
add_library( MyOpenCV::test   ALIAS test )
add_library( MyOpenCV::input   ALIAS input )
add_library( MyOpenCV::objects ALIAS objects)