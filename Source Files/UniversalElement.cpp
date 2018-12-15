//
// Created by new on 2018-11-13.
//

#include "../Header Files/UniversalElement.h"

UniversalElement::UniversalElement() {
    coordinatesTab = make_unique<unique_ptr<double[]>[]>(4);
    for (int i = 0; i < 4; ++i) {
        tab = make_unique<double[]>(2);
        coordinatesTab[i] = move(tab);


    }

    coordinatesOfUniversalElement = make_unique<Node[]>(8);

setValueOfUniversalElementCoordinates();

}

UniversalElement::~UniversalElement() {

}

void UniversalElement::setValueOfUniversalElementCoordinates() {
    double ksi, eta;
    for (int i = 0; i < 8; ++i) {

        switch (i) {
            case 0:
                ksi = -0.57735;
                eta = -1;
                break;
            case 1:
                ksi = 0.57735;;
                eta = -1;
                break;
            case 2:
                ksi =1;
                eta =-0.577735;
                break;
            case 3:
                ksi =1;
                eta =0.57735;
                break;
            case 4:
                ksi =0.57735;
                eta =1;
                break;
            case 5:
                ksi =-0.57735;
                eta =1;
                break;
            case 6:
                ksi =-1;
                eta =0.57735;
                break;

            case 7:
                ksi =-1;
                eta =-0.57735;
                break;
            default:
                break;

        }

        coordinatesOfUniversalElement[i].x=ksi;
        coordinatesOfUniversalElement[i].y=eta;


    }


}