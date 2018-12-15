#include <iostream>
#include <iomanip>
#include "../libs/json.hpp"
#include "../Header Files/FileReader.h"
#include "../Header Files/Grid.h"
#include "../Header Files/FiniteElement.h"
#include "../Header Files/Matrix.h"
#include "../Header Files/ShapeFunction.h"
#include "../Header Files/UniversalElement.h"

using namespace std;


int main() {

    auto grid = make_shared<Grid>();
//    grid->setNodesCordinates();
   // grid->showNodesCordinates();
//    grid->setElementID();
//    grid->setNodesInElement();
//    grid->setBCInNodesElement();
    // grid->showElementID();
    //shared_ptr<Element> element = make_shared<Element>(30);
    //element->showNodes();
//    FileReader fileReader("params.json");
//    fileReader.readFromFile();
//    vector<shared_ptr<Matrix>> matrixVec;

//    grid->setMatrixs();
//    cout << endl;
//    grid->setValueOfMatrixHAndVectorP();
//
//    grid->showGlobalMatrixC();
//    cout << endl;
//    grid->showGlobalMatrixH();
//    cout << endl;
//    grid->showGlobalVectorP();
    grid->calculateTemperatures();


    return 0;

}



//
//UniversalElement element1;



//ShapeFunction shape;
//FileReader fileReader("params.json");
//fileReader.readFromFile();

//unique_ptr<Element>element=make_unique<Element>(30);
//Matrix*matrix=new Matrix(new Element(30));
//unique_ptr<Matrix>matrix=make_unique<Matrix>(move(element)



