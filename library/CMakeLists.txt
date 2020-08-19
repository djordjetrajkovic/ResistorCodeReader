# ./library/CMakeLists.txt

cmake_minimum_required( VERSION 3.16 )

project( OpenCVLibs
        VERSION 1.0.0
        DESCRIPTION "The internal libraries."
    )

# Find Packege
find_package(OpenCV 4.4)

# An classification library
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

# An segmentation library
add_library( segmentation SHARED )

target_sources( segmentation 
    PRIVATE "src/segmentation.cpp"
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/segmentation.h"        
)
message( ${CMAKE_CURRENT_SOURCE_DIR} )
target_include_directories( segmentation PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" )

target_link_libraries( segmentation PUBLIC opencv_highgui )
target_link_libraries( segmentation PUBLIC opencv_imgproc )
target_link_libraries( segmentation PUBLIC opencv_video   )
target_link_libraries( segmentation PUBLIC opencv_core    )
target_link_libraries( segmentation PUBLIC opencv_shape   )
target_link_libraries( segmentation PUBLIC classification )
target_link_libraries( segmentation PUBLIC objects        )

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



# Create ALIAS targets.
add_library( MyOpenCV::classification ALIAS classification ) 
add_library( MyOpenCV::segmentation   ALIAS segmentation )
add_library( MyOpenCV::test   ALIAS test )
add_library( MyOpenCV::input   ALIAS input )
add_library( MyOpenCV::objects ALIAS objects)