//
// Created by new on 2018-11-13.
//

#ifndef UNTITLED2_UNIVERSALELEMENT_H
#define UNTITLED2_UNIVERSALELEMENT_H

#include <memory>
#include <vector>
#include <iostream>
#include "../Header Files/Node.h"
using namespace std;
class UniversalElement {
public:
    //tutaj wrzucamy wezly w celu przechowywania wspolrzednych punktow(ksi,eta) dodatkowych wezlow
    unique_ptr<unique_ptr<double[]>[]>coordinatesTab;
    unique_ptr<double[]>tab;
    //wspolrzedne wezlow dodatkowych w elemencie uniwersalnym
    unique_ptr<Node[]>coordinatesOfUniversalElement;
    void setValueOfUniversalElementCoordinates();
    void setValueOfCoordinatesTab();


    UniversalElement();

    virtual ~UniversalElement();


};


#endif //UNTITLED2_UNIVERSALELEMENT_H
