//
// Created by new on 2018-10-31.
//

#ifndef UNTITLED2_MATRIX_H
#define UNTITLED2_MATRIX_H

#include <memory>
#include <iostream>

#include "FileReader.h"
#include "FiniteElement.h"
#include "ShapeFunction.h"
#include "UniversalElement.h"

using namespace std;

class Matrix {

private:
    unique_ptr<double[]> tab;
    unique_ptr<unique_ptr<double[]>[]> derivativeOfShapeFunctionKsi;


    unique_ptr<unique_ptr<double[]>[]> derivativeOfShapeFunctionEta;
    unique_ptr<unique_ptr<double[]>[]>matrixJ;
    unique_ptr<unique_ptr<double[]>[]>matrixJFinall;
    unique_ptr<double[]>detJ;
    unique_ptr<unique_ptr<double[]>[]>derivativeOfShapeFunctionX;
    unique_ptr<unique_ptr<double[]>[]>derivativeOfShapeFunctionY;

    unique_ptr<unique_ptr<double[]>[]> multiplicationMatrixForFirstPointX;
    unique_ptr<unique_ptr<double[]>[]> multiplicationMatrixForSecondPointX;
    unique_ptr<unique_ptr<double[]>[]> multiplicationMatrixForThirdPointX;
    unique_ptr<unique_ptr<double[]>[]> multiplicationMatrixForFourthPointX;


    unique_ptr<unique_ptr<double[]>[]> multiplicationMatrixForFirstPointY;
    unique_ptr<unique_ptr<double[]>[]> multiplicationMatrixForSecondPointY;
    unique_ptr<unique_ptr<double[]>[]> multiplicationMatrixForThirdPointY;
    unique_ptr<unique_ptr<double[]>[]> multiplicationMatrixForFourthPointY;

    unique_ptr<unique_ptr<double[]>[]> matrixH;
    unique_ptr<unique_ptr<double[]>[]>matrixC;
    unique_ptr<double[]>vectorP;


   // Element *element; //change to smart pointer and check how to send smart pointer to constructor
    unique_ptr<FileReader> fileReader;
    double c;
    double ro;
    double alfa;
    double det;
    ShapeFunction shapeFunction;
    UniversalElement universalElement;



public:
    Matrix();

    Matrix(shared_ptr<Element>);
    shared_ptr<Element>element;

    //Matrix(Element *);

    ~Matrix();


    void setValueOfDerivativeShapeFunctionKsi();

    void setValueOfDerivativeShapeFunctionEta();

    void setValueOfMatrixJ();

    void setValueOfDetJ();

    void setValueOfMatrixJFinall();

    void setValueOfDerivativeShapeFunctionX();

    void setValueOfDerivativeShapeFunctionY();


    void setValueOfMultiplicationMatrix();

    void setValueOfMatrixH();

    void setValueOfMatrixC();


    const unique_ptr<FileReader> &getFileReader() const;


};


#endif //UNTITLED2_MATRIX_H
