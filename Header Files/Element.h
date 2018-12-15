//
// Created by new on 2018-10-18.
//

#ifndef UNTITLED2_ELEMENT_H
#define UNTITLED2_ELEMENT_H

#include<iostream>
#include <memory>
#include <vector>
#include "Node.h"
#include "FileReader.h"

using namespace std;

class Element {

    //   double id[4];
public:
    unique_ptr<FileReader>fileReader;
    unique_ptr<int[]> id;
    unique_ptr<Node[]> nodeTab;
    unique_ptr<unique_ptr<double[]>[]> matrixH;
    unique_ptr<unique_ptr<double[]>[]> matrixC;
    unique_ptr<double[]>vectorP;
    void setBCInNodesElement(bool,bool,bool,bool);

    double k; //wspol przewodzenia
    void showId();
    void showNodes();
    void setNodeValTest();

    Element();
    Element(double);

    ~Element();
};


#endif //UNTITLED2_ELEMENT_H
