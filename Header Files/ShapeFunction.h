//
// Created by new on 2018-11-13.
//

#ifndef UNTITLED2_SHAPEFUNCTION_H
#define UNTITLED2_SHAPEFUNCTION_H

#include <vector>
#include <iostream>
#include "FileReader.h"

using namespace std;

class ShapeFunction {
private:
    double N1, N2, N3, N4;
    FileReader fileReader{"params.json"};

    unique_ptr<double[]> tab;
public:
    unique_ptr<unique_ptr<double[]>[]> shapeFunctionsTab;

    ShapeFunction();

    virtual ~ShapeFunction();

    double getN1() const;

    double getN2() const;

    double getN3() const;

    double getN4() const;

    void setN1(double, double);

    void setN2(double, double);

    void setN3(double, double);

    void setN4(double, double);

    void setValueOfShapeFunctionsTab();


};


#endif //UNTITLED2_SHAPEFUNCTION_H
