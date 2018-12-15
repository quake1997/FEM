//
// Created by new on 2018-10-25.
//

#ifndef UNTITLED2_FINITEELEMENT_H
#define UNTITLED2_FINITEELEMENT_H

#include <memory>
#include <iostream>

#include "Element.h"
#include "Node.h"
using namespace std;

class FiniteElement : public Element {
public:
    unique_ptr<Node[]> nodeTab;

    void setFiniteElementId();

    void setNodeVal();

    FiniteElement();


    ~FiniteElement();

};


#endif //UNTITLED2_FINITEELEMENT_H
