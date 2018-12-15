//
// Created by new on 2018-10-18.
//

#ifndef UNTITLED2_GRID_H
#define UNTITLED2_GRID_H


#include "Node.h"
#include "Element.h"
#include "FileReader.h"
#include "Matrix.h"
#include <string>
#include <iostream>
#include<memory>
#include<vector>

using namespace std;

class Grid {
public:

    unique_ptr<unique_ptr<double[]>[]> globalMatrixH;
    unique_ptr<unique_ptr<double[]>[]> globalMatrixC;
    unique_ptr<double[]> globalVectorP;
    unique_ptr<double[]> vectorP; //wektor P bez daszka ten podstaowowy globalny nie mylisc z globalVectorP ktory jest wektorem z daszkiem
    vector<long double> vectorOfTemperatures;
    unique_ptr<double[]> tab;
    vector<shared_ptr<Node>> nodeTab;
    unique_ptr<unique_ptr<double[]>[]> matrixHAndVectorP;



    vector<shared_ptr<Element>> elementTab;

    //unique_ptr<FileReader> fileReader;
    FileReader fileReader{"params.json"};
    double a=fileReader.getNl()*fileReader.getNl();

    int modifiedIndexI, modifiedIndexJ;

    void setNodesCordinates();

    void setNodeTab();

    void setElementTab();

    void setElementID();

    void showElementID();

    void showNodesCordinates();

    void setNodesInElement();

    void setBCInNodesElement();

    void setValueOfGlobalMatrix(shared_ptr<Element>);

    void setValueOfVectorP(shared_ptr<Element>);

    void setValueOfMatrixHAndVectorP();

    void calculateTemperatures();

    void upgradeVectorP();

    void modifyVectorP();

    bool gaussMethod(int);

    void showGlobalVectorP();

    void showGlobalMatrixH();

    void showGlobalMatrixC();

    void setMatrixs();

    void modifyIndexes(int, int, shared_ptr<Element>);

    Grid();

    ~Grid();
};


#endif //UNTITLED2_GRID_H
