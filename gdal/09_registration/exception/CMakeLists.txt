# add_library(BasicException BasicException.cpp BasicException.h)

# add_library(ImageCalcException ImageCalcException.cpp ImageCalcException.h)
# target_link_libraries(ImageCalcException ImageException)

# add_library(ImageException ImageException.cpp ImageException.h)

# add_library(MathException MathException.cpp MathException.h)

#target_include_directories(MathFunctions
#          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
#          )
# define sources
set(EXCEPTIONS 
  BasicException.cpp 
  ImageBandException.cpp
  ImageCalcException.cpp 
  ImageException.cpp 
  InputStreamException.cpp
  MathException.cpp 
  MatricesException.cpp
  OutputStreamException.cpp
  RegistrationException.cpp
  TextException.cpp
  VectorsException.cpp
  VectorsException.h
  TextException.h
  RegistrationException.h
  OutputStreamException.h
  MatricesException.h
  MathException.h
  InputStreamException.h
  ImageException.h
  ImageCalcException.h
  ImageBandException.h 
  BasicException.h)

add_library(${EXCEPTIONS_LIB_NAME} SHARED
  ${EXCEPTIONS}
)

# target_include_directories(${EXCEPTIONS_LIB_NAME}
#           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
#           )