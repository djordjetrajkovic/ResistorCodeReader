# ./app/CMakeLists.txt
cmake_minimum_required( VERSION 3.15...3.17 )

project( MyOpenCVProject
        VERSION 1.0
        DESCRIPTION "Test framework for opencv."
)

add_executable( Project )
target_sources( Project PRIVATE "src/main.cpp" )
target_link_libraries( Project PRIVATE MyOpenCV::classification )
target_link_libraries( Project PRIVATE MyOpenCV::segmentation )
target_link_libraries( Project PRIVATE MyOpenCV::test )
target_link_libraries( Project PRIVATE MyOpenCV::input )
target_link_libraries( Project PRIVATE MyOpenCV::objects )