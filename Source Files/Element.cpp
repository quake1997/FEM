//
// Created by new on 2018-10-18.
//

#include "../Header Files/Element.h"


Element::Element() {
    id = make_unique<int[]>(4);
    nodeTab = make_unique<Node[]>(4);
    fileReader=make_unique<FileReader>("params.json");
    setNodeValTest();
    setBCInNodesElement(true,false,false,false);



}

Element::Element(double k) {
    this->k = k;
    id = make_unique<int[]>(4);
    nodeTab = make_unique<Node[]>(4);
    setNodeValTest();
    setBCInNodesElement(true,true,false,false);

}

Element::~Element() {
}

void Element::showId() {


    for (int i = 0; i < 4; i++) {
        cout << id[i] << endl;
    }

}

void Element::setNodeValTest() {

    nodeTab[0].x = 0;
    nodeTab[0].y = 0;

    nodeTab[1].x = 0.025;
    nodeTab[1].y = 0;

    nodeTab[2].x = 0.025;
    nodeTab[2].y = 0.025;

    nodeTab[3].x = 0;
    nodeTab[3].y = 0.025;


}

void Element::showNodes() {

    for (int i = 0; i < 4; ++i) {

        cout << nodeTab[i].x << " " << nodeTab[i].y <<" "<<nodeTab[i].BC<< endl;

    }
}

void Element::setBCInNodesElement(bool param1, bool param2, bool param3, bool param4) {



    nodeTab[0].BC=param1;
    nodeTab[1].BC=param2;
    nodeTab[2].BC=param3;
    nodeTab[3].BC=param4;




}