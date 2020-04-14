# ./external/opencv/CMakeLists.txt

set( OPEN_CV_VERSION 4 )

find_package(OpenCV ${OPEN_CV_VERSION} REQUIRED COMPONENTS core imgproc video highgui)

set_target_properties(
    OpenCV::core
    OpenCV::video
    OpenCV::imgproc
    OpenCV::highgui
    PROPERTIES IMPORTED_GLOBAL TRUE
)