#include <iostream>
#include "../libs/json.hpp"
#include "../Header Files/FileReader.h"
#include "../Header Files/Grid.h"




using namespace std;

int main() {

 auto grid =make_shared<Grid>();
    grid->setNodesCordinates();
    grid->showNodesCordinates();
    grid->setElementID();
    grid->showElementID();


    return 0;
}




