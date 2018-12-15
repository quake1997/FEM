//
// Created by new on 2018-11-13.
//

#include "../Header Files/ShapeFunction.h"

ShapeFunction::ShapeFunction() {
    shapeFunctionsTab=make_unique<unique_ptr<double[]>[]>(4);
    for (int i = 0; i < 4; ++i) {
        tab=make_unique<double[]>(4);
        shapeFunctionsTab[i]=move(tab);
    }
   setValueOfShapeFunctionsTab();



}

ShapeFunction::~ShapeFunction() {

}

double ShapeFunction::getN1() const {
    return N1;
}

double ShapeFunction::getN2() const {
    return N2;
}

double ShapeFunction::getN3() const {
    return N3;
}

double ShapeFunction::getN4() const {
    return N4;
}

void ShapeFunction::setN1(double ksi,double eta ) {
   N1=0.25*(1-ksi)*(1-eta);
}

void ShapeFunction::setN2(double ksi,double eta) {
    N2=0.25*(1+ksi)*(1-eta);
}

void ShapeFunction::setN3(double ksi,double eta) {
    N3=0.25*(1+ksi)*(1+eta);
}

void ShapeFunction::setN4(double ksi,double eta) {
    N4=0.25*(1-ksi)*(1+eta);
}

void ShapeFunction::setValueOfShapeFunctionsTab() {

    for (int i = 0; i <4 ; ++i) {
        setN1(fileReader.getKsiTab()[i],fileReader.getEtaTab()[i]);
        setN2(fileReader.getKsiTab()[i],fileReader.getEtaTab()[i]);
        setN3(fileReader.getKsiTab()[i],fileReader.getEtaTab()[i]);
        setN4(fileReader.getKsiTab()[i],fileReader.getEtaTab()[i]);
        shapeFunctionsTab[i][0]=N1;
        shapeFunctionsTab[i][1]=N2;
        shapeFunctionsTab[i][2]=N3;
        shapeFunctionsTab[i][3]=N4;


    }


}
