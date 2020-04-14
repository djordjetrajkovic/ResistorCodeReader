# ./external/opencv/CMakeLists.txt

set( OPEN_CV_VERSION 4 )

find_package(OpenCV ${OPEN_CV_VERSION} REQUIRED COMPONENTS core imgproc video highgui)

set_target_properties(
    opencv_core
    opencv_video
    opencv_imgproc
    opencv_highgui
    PROPERTIES IMPORTED_GLOBAL TRUE
)