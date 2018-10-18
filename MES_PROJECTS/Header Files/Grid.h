//
// Created by new on 2018-10-18.
//

#ifndef UNTITLED2_GRID_H
#define UNTITLED2_GRID_H


#include "Node.h"
#include "Element.h"
#include "FileReader.h"
#include <string>
#include <iostream>
#include<memory>
#include<vector>

class Grid {
public:


    vector<unique_ptr<Node>>nodeTab;

    vector<unique_ptr<Element>>elementTab;

    unique_ptr<FileReader>fileReader;
    void setNodesCordinates();
    void setNodeTab();
    void setElementTab();
    void setElementID();
    void showElementID();
    void showNodesCordinates();

    Grid();

    ~Grid();
};


#endif //UNTITLED2_GRID_H
