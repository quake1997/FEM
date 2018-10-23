#include <iostream>
#include "../libs/json.hpp"
#include "../Header Files/FileReader.h"
#include "../Header Files/Grid.h"




using namespace std;
//cos nie dziala, ale chuj wie co xd
int main() {
    auto grid =make_shared<Grid>();
    grid->setNodesCordinates();
    grid->showNodesCordinates();
    grid->setElementID();
    grid->showElementID();



    return 0;
}




