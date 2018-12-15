//
// Created by new on 2018-10-25.
//

#include "../Header Files/FiniteElement.h"

FiniteElement::FiniteElement():Element() {
    nodeTab=make_unique<Node[]>(4);
    setNodeVal();



}



FiniteElement::~FiniteElement(){


}

void FiniteElement::setFiniteElementId() {

    for (int i = 0; i < 4; ++i) {
        id[i]=i+1;
    }
}

void FiniteElement::setNodeVal() {

    nodeTab[0].x=0;
    nodeTab[0].y=0;

    nodeTab[1].x=0.025;
    nodeTab[1].y=0;

    nodeTab[2].x=0.025;
    nodeTab[2].y=0.025;

    nodeTab[3].x=0;
    nodeTab[3].y=0.025;



}
