cmake_minimum_required(VERSION 3.12)
project(untitled2)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled2 "Source Files/main.cpp" "Source Files/FileReader.cpp" "Header Files/FileReader.h" "Source Files/Element.cpp" "Header Files/Element.h" "Source Files/Node.cpp" "Header Files/Node.h" "Source Files/Grid.cpp" "Header Files/Grid.h" "Source Files/FiniteElement.cpp" "Header Files/FiniteElement.h" "Source Files/Matrix.cpp" "Header Files/Matrix.h" "Source Files/UniversalElement.cpp" "Header Files/UniversalElement.h" "Source Files/ShapeFunction.cpp" "Header Files/ShapeFunction.h")