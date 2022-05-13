add_library(BasicException BasicException.cpp BasicException.h)

add_library(ImageCalcException ImageCalcException.cpp ImageCalcException.h)
target_link_libraries(ImageCalcException ImageException)

add_library(ImageException ImageException.cpp ImageException.h)

add_library(MathException MathException.cpp MathException.h)

#target_include_directories(MathFunctions
#          INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
#          )