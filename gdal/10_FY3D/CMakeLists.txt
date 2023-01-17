cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(fy3_mersi_process)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(LIB_PATH_1 /usr/local/lib CACHE PATH "MAIN Library PATH")
include_directories(/usr/local/include)
set(HDF5_LIBRARIES -L${LIB_PATH_1} -lhdf5 -lhdf5_cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_library(FY3D_MERSI_L1_Reader FY3D_MERSI_L1_Reader.cpp FY3D_MERSI_L1_Reader.h h5_read.cpp h5_read.h)
target_link_libraries(FY3D_MERSI_L1_Reader ${HDF5_LIBRARIES})

# add the executable
add_executable(fy3_mersi_process fy3_mersi_process.cpp)

target_link_libraries(fy3_mersi_process PUBLIC FY3D_MERSI_L1_Reader)