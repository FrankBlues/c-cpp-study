# add_library(BasicException BasicException.cpp BasicException.h)

# add_library(ImageCalcException ImageCalcException.cpp ImageCalcException.h)
# target_link_libraries(ImageCalcException ImageException)

# add_library(ImageException ImageException.cpp ImageException.h)

# add_library(MathException MathException.cpp MathException.h)

#target_include_directories(MathFunctions
#          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
#          )
# define sources
set(MATH_SOURCE 
  MathsUtils.cpp 
  Matrices.cpp
  PolyFit.cpp 
  SingularValueDecomposition.cpp 
  Vectors.cpp
  MathsUtils.h
  Matrices.h
  PolyFit.h
  SingularValueDecomposition.h
  Vectors.h
)

add_library(${MATHS_LIB_NAME} SHARED
  ${MATH_SOURCE}
)
target_link_libraries(${MATHS_LIB_NAME} ${EXCEPTIONS_LIB_NAME} 
  ${GDAL_LIBRARIES} ${BOOST_LIBRARIES} ${GSL_LIBRARIES})

# target_include_directories(${MATHS_LIB_NAME}
#   INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
#   )