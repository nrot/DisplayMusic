cmake_minimum_required(VERSION 3.5)
project( DisplayMusic )
set(SRC_LIST DisplayMusic.cpp
             apps/apps_wave_file.h apps/apps_wave_file.cpp
             apps/apps_arrays.h apps/apps_arrays.cpp
             examples/ampl_view.h examples/ampl_view.cpp examples/ampl_edit.h)
add_executable( ${PROJECT_NAME} ${SRC_LIST})

target_link_libraries( DisplayMusic ${OpenCV_LIBS} )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

target_link_libraries(${PROJECT_NAME} PUBLIC Aquila)
target_link_libraries(${PROJECT_NAME} PUBLIC gd)

find_package(OpenCV 3.1.0 REQUIRED COMPONENTS opencv_core )
if(NOT OpenCV_FOUND)
    message(SEND_ERROR "Failed to find OpenCV")
    return()
else()
    #include_directories( ${OpenCV_INCLUDE_DIRS} )
    message(STATUS "Find OpenCV = OK")
endif()

