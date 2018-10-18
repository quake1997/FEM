//
// Created by new on 2018-10-18.
//

#include "../Header Files/Grid.h"


Grid::Grid() {

    fileReader=make_unique<FileReader>("params.json");
    fileReader->readFromFile();
    setElementTab();
    setNodeTab();

}




Grid::~Grid() {
}


void Grid::setNodeTab() {

    for (int i = 0; i < fileReader->getNh()*fileReader->getNl(); i++) {
        //	nodeTab.push_back(unique_ptr<Node>(new Node()));

        nodeTab.emplace_back(new Node());

    }
//cout<<(fileReader->getNl()*fileReader->getNh())<<endl;

}

void Grid::setElementTab() {

    for (int i = 0; i < (fileReader->getNh()-1)*(fileReader->getNl()-1); i++) {
        //	elementTab.push_back(unique_ptr<Element>(new Element()));

        elementTab.emplace_back(new Element());


    }

}

void Grid::setNodesCordinates() {

    cout<<fileReader.get()<<endl;
    double dh = fileReader->getH() / (fileReader->getNh() - 1);
    double dl = fileReader->getL() / (fileReader->getNl() - 1);
    int nhVal = static_cast<int>(fileReader->getNh());

    nodeTab[0]->x = 0;
    nodeTab[0]->y = 0;
    int nodeVal = 0;
    for (int i = 1; i < (fileReader->getNh() * fileReader->getNl()); i++) {


        if (i - nhVal == nodeVal) {
            nodeVal = i;
            nodeTab[i]->x = nodeTab[i - 1]->x + dl;
            nodeTab[i]->y = 0;

        } else {
            nodeTab[i]->x = nodeTab[i - 1]->x;

            nodeTab[i]->y = nodeTab[i - 1]->y + dh;

        }


    }


}

void Grid::setElementID() {
    int counter = 0;
    int loop = (fileReader->getNh() - 1) * (fileReader->getNl() - 1);
    int nhVal = static_cast<int>(fileReader->getNh());
    int nlVal = static_cast<int>(fileReader->getNl());
    for (int i = 1; i <= fileReader->getNh() * fileReader->getNl(); i++) {
        if (i % nhVal == 0)continue;


        if (i > 24 - nhVal)break;


        elementTab[counter]->id[0] = i;
        elementTab[counter]->id[1] = i + fileReader->getNh();
        elementTab[counter]->id[2] = elementTab[counter]->id[1] + 1;
        elementTab[counter]->id[3] = elementTab[counter]->id[0] + 1;

        counter++;


    }

}

void Grid::showElementID() {


    int i = 0;

    for (vector<unique_ptr<Element>>::iterator iter = elementTab.begin(); iter != elementTab.end(); iter++) {

        cout << "Element nr " << ++i << endl;
        (*iter)->showId();
        //cout << (*iter) << endl;

    }


};

void Grid::showNodesCordinates() {

    int i = 0;

    for (vector<unique_ptr<Node>>::iterator it = nodeTab.begin(); it != nodeTab.end(); it++) {

        cout << "wezel nr " << ++i << " " << "wspol x: " << (*it)->x << " " << "wspol y: " << (*it)->y << endl;
    }


}

