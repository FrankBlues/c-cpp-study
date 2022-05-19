set(BOOST_INCLUDE_DIR /usr/include/boost CACHE PATH "Include PATH for Boost")
set(BOOST_LIB_PATH /usr/local/lib CACHE PATH "Library PATH for Boost")

set(GSL_INCLUDE_DIR /usr/include/gsl CACHE PATH "Include PATH for GSL")
set(GSL_LIB_PATH /usr/local/lib CACHE PATH "Library PATH for GSL")

set(GDAL_INCLUDE_DIR /usr/include CACHE PATH "Include PATH for GDAL")
set(GDAL_LIB_PATH /usr/lib CACHE PATH "Library PATH for GDAL")

set(COMMON_LIB_NAME common)
set(EXCEPTIONS_LIB_NAME exceptions)
set(IMG_LIB_NAME img)
set(MATHS_LIB_NAME maths)
set(UTILS_LIB_NAME utils)



include_directories(${BOOST_INCLUDE_DIR})
set(BOOST_LIBRARIES -L${BOOST_LIB_PATH} ) # -lboost_filesystem -lboost_system -lboost_date_time

include_directories(${GDAL_INCLUDE_DIR})
set(GDAL_LIBRARIES -L${GDAL_LIB_PATH} -lgdal)

include_directories(${GSL_INCLUDE_DIR})
set(GSL_LIBRARIES -L${GSL_LIB_PATH} -lgsl -lgslcblas)

# include_directories("exception")
# include_directories("common")
include_directories(${CMAKE_CURRENT_SOURCE_DIR})



cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(RegistrationTest)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(common)
add_subdirectory(exception)
add_subdirectory(img)
add_subdirectory(math)
add_subdirectory(utils)

add_library(ImageRegistration BasicImageRegistration.cpp BasicImageRegistration.h 
  ImageRegistration.cpp ImageRegistration.h ImageSimilarityMetric.h 
  StandardImageSimilarityMetrics.cpp StandardImageSimilarityMetrics.h)
target_link_libraries(ImageRegistration ${COMMON_LIB_NAME} ${EXCEPTIONS_LIB_NAME} ${IMG_LIB_NAME} ${MATHS_LIB_NAME} ${BOOST_LIBRARIES} ${GDAL_LIBRARIES} ${GSL_LIBRARIES})

# list(APPEND EXTRA_LIBS BasicException MathException ImageException ImageCalcException CalcImageValue ImageSimilarityMetric)

# add the executable
add_executable(BasicRegistrationTest BasicRegistrationTest.cpp)


target_link_libraries(BasicRegistrationTest PUBLIC ImageRegistration ${GDAL_LIBRARIES})

#target_link_libraries(ImageRegistration ${BOOST_LIBRARIES} ${GDAL_LIBRARIES})
# 添加动态连接库的路径
# link_directories(${PROJECT_SOURCE_DIR}/lib)
# target_link_libraries(ImageRegistration -lgdal)

# target_include_directories(${MATHS_LIB_NAME} PUBLIC
# 	                           "${PROJECT_BINARY_DIR}"
# 				                  )
