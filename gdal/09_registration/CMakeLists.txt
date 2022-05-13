# set(BOOST_INCLUDE_DIR /usr/include/boost CACHE PATH "Include PATH for Boost")
# set(BOOST_LIB_PATH /usr/local/lib CACHE PATH "Library PATH for Boost")

# set(GSL_INCLUDE_DIR /usr/include/gsl CACHE PATH "Include PATH for GSL")
# set(GSL_LIB_PATH /usr/local/lib CACHE PATH "Library PATH for GSL")

# set(GDAL_INCLUDE_DIR /usr/include CACHE PATH "Include PATH for GDAL")
# set(GDAL_LIB_PATH /usr/lib CACHE PATH "Library PATH for GDAL")


cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(ImageRegistration)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(exception)

add_library(CalcImageValue CalcImageValue.cpp CalcImageValue.h)
target_link_libraries(CalcImageValue ImageCalcException)

add_library(ImageSimilarityMetric ImageSimilarityMetric.h StandardImageSimilarityMetrics.h StandardImageSimilarityMetrics.cpp)
target_link_libraries(ImageSimilarityMetric ImageCalcException CalcImageValue)


list(APPEND EXTRA_LIBS BasicException MathException ImageException ImageCalcException CalcImageValue ImageSimilarityMetric)

# add the executable
add_executable(ImageRegistration BasicRegistrationTest.cpp)


target_link_libraries(ImageRegistration PUBLIC ${EXTRA_LIBS} -lgdal)

# target_link_libraries(ImageRegistration ${BOOST_LIBRARIES} ${GDAL_LIBRARIES})
# 添加动态连接库的路径
# link_directories(${PROJECT_SOURCE_DIR}/lib)
# target_link_libraries(ImageRegistration -lgdal)

#target_include_directories(ImageRegistration PUBLIC
#	                           "${PROJECT_BINARY_DIR}"
#				                              )
