//
// Created by new on 2018-10-18.
//

#include "../Header Files/Grid.h"


Grid::Grid(){
    //vectorOfTemperatures.push_back(100);
  //  fileReader = make_unique<FileReader>("params.json");
   // fileReader.readFromFile();
   vectorOfTemperatures.assign(fileReader.getNl() * fileReader.getNh(),fileReader.getInitialTemperature());
   setElementTab();
    setNodeTab();
    globalMatrixH = make_unique<unique_ptr<double[]>[]>(fileReader.getNl() * fileReader.getNh());
    globalMatrixC = make_unique<unique_ptr<double[]>[]>(fileReader.getNl() * fileReader.getNh());
    globalVectorP = make_unique<double[]>(fileReader.getNl() * fileReader.getNh());
    vectorP = make_unique<double[]>(fileReader.getNl() * fileReader.getNh());

    matrixHAndVectorP = make_unique<unique_ptr<double[]>[]>(fileReader.getNl() * fileReader.getNh());
    //wywalic to z konstruktora
    for (int i = 0; i < fileReader.getNl() * fileReader.getNh(); i++) {
        tab = make_unique<double[]>(fileReader.getNl() * fileReader.getNh() + 1);
        globalMatrixH[i] = move(tab);


    }

    for (int i = 0; i < fileReader.getNl() * fileReader.getNh(); i++) {
        tab = make_unique<double[]>(fileReader.getNl() * fileReader.getNh() + 1);
        globalMatrixC[i] = move(tab);


    }
    for (int i = 0; i < fileReader.getNl() * fileReader.getNh(); i++) {
        tab = make_unique<double[]>(fileReader.getNl() * fileReader.getNh() + 1);
        matrixHAndVectorP[i] = move(tab);


    }

    setNodesCordinates();
    setElementID();
    setNodesInElement();
    setBCInNodesElement();
    setMatrixs();

}


Grid::~Grid() {
}


void Grid::setNodeTab() {

    for (int i = 0; i < fileReader.getNh() * fileReader.getNl(); i++) {
        //	nodeTab.push_back(unique_ptr<Node>(new Node()));

        nodeTab.emplace_back(new Node());

    }
//cout<<(fileReader.getNl()*fileReader.getNh())<<endl;

}

void Grid::setElementTab() {

    for (int i = 0; i < (fileReader.getNh() - 1) * (fileReader.getNl() - 1); i++) {
        //	elementTab.push_back(unique_ptr<Element>(new Element()));

        elementTab.emplace_back(new Element(fileReader.getK()));


    }

}

void Grid::setNodesCordinates() {


    double dh = fileReader.getH() / (fileReader.getNh() - 1);
    double dl = fileReader.getL() / (fileReader.getNl() - 1);
    int nhVal = static_cast<int>(fileReader.getNh());

    nodeTab[0]->x = 0;
    nodeTab[0]->y = 0;
    int nodeVal = 0;
    for (int i = 1; i < (fileReader.getNh() * fileReader.getNl()); i++) {


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
    int loop = (fileReader.getNh() - 1) * (fileReader.getNl() - 1);
    int nhVal = static_cast<int>(fileReader.getNh());
    int nlVal = static_cast<int>(fileReader.getNl());
    for (int i = 1; i <= fileReader.getNh() * fileReader.getNl(); i++) {
        if (i % nhVal == 0)continue;


        if (i > nhVal * nlVal - nhVal)break;


        elementTab[counter]->id[0] = i;
        elementTab[counter]->id[1] = i + fileReader.getNh();
        elementTab[counter]->id[2] = elementTab[counter]->id[1] + 1;
        elementTab[counter]->id[3] = elementTab[counter]->id[0] + 1;

        counter++;


    }

}

void Grid::showElementID() {


    int i = 0;

    for (vector<shared_ptr<Element >>::iterator iter = elementTab.begin(); iter != elementTab.end(); iter++) {
        cout << "Element nr " << ++i << endl;
        // (*iter)->showId();
        (*iter)->showId();
        //cout << (*iter) << endl;


    }


};

void Grid::showNodesCordinates() {

    int i = 0;

    for (vector<shared_ptr<Node >>::iterator it = nodeTab.begin(); it != nodeTab.end();
         it++) {

        cout << "wezel nr " << ++i << " " << "wspol x: " << (*it)->x << " " << "wspol y: " << (*it)->y << endl;
    }


}

void Grid::setNodesInElement() {
    int counter = 0;

    int nhVal = static_cast<int>(fileReader.getNh());
    int nlVal = static_cast<int>(fileReader.getNl());
    for (int i = 1; i <= nodeTab.size(); i++) {
        if (i % nhVal == 0)continue;


        if (i > nhVal * nlVal - nhVal)break;


        elementTab[counter]->nodeTab[0].x = nodeTab[i - 1]->x;
        elementTab[counter]->nodeTab[0].y = nodeTab[i - 1]->y;

        elementTab[counter]->nodeTab[1].x = nodeTab[(i + fileReader.getNh()) - 1]->x;
        elementTab[counter]->nodeTab[1].y = nodeTab[(i + fileReader.getNh()) - 1]->y;

        elementTab[counter]->nodeTab[2].x = nodeTab[(i + fileReader.getNh())]->x;
        elementTab[counter]->nodeTab[2].y = nodeTab[(i + fileReader.getNh())]->y;


        elementTab[counter]->nodeTab[3].x = nodeTab[i]->x;
        elementTab[counter]->nodeTab[3].y = nodeTab[i]->y;


        counter++;


    }


}

void Grid::setBCInNodesElement() {
    //ustawimy flage BC dla kazdego wezla w elemencie, ogrzewamy bo obwodzie
    int counter = 0;
    for (int i = 1; i <= fileReader.getNh() - 1; ++i) {
        for (int j = 1; j <= fileReader.getNh() - 1; ++j) {
            if (i == 1) {
                if (j == 1) {
                    elementTab[counter]->nodeTab[0].BC = true;
                    elementTab[counter]->nodeTab[1].BC = true;
                    elementTab[counter]->nodeTab[2].BC = false;
                    elementTab[counter]->nodeTab[3].BC = true;
                } else if (j > 1 && j < fileReader.getNh() - 1) {
                    elementTab[counter]->nodeTab[0].BC = true;
                    elementTab[counter]->nodeTab[1].BC = false;
                    elementTab[counter]->nodeTab[2].BC = false;
                    elementTab[counter]->nodeTab[3].BC = true;

                } else {
                    elementTab[counter]->nodeTab[0].BC = true;
                    elementTab[counter]->nodeTab[1].BC = false;
                    elementTab[counter]->nodeTab[2].BC = true;
                    elementTab[counter]->nodeTab[3].BC = true;

                }


            } else if (i > 1 && i < fileReader.getNh() - 1) {
                if (j == 1) {
                    elementTab[counter]->nodeTab[0].BC = true;
                    elementTab[counter]->nodeTab[1].BC = true;
                    elementTab[counter]->nodeTab[2].BC = false;
                    elementTab[counter]->nodeTab[3].BC = false;
                } else if (j > 1 && j < fileReader.getNh() - 1) {
                    elementTab[counter]->nodeTab[0].BC = false;
                    elementTab[counter]->nodeTab[1].BC = false;
                    elementTab[counter]->nodeTab[2].BC = false;
                    elementTab[counter]->nodeTab[3].BC = false;

                } else {
                    elementTab[counter]->nodeTab[0].BC = false;
                    elementTab[counter]->nodeTab[1].BC = false;
                    elementTab[counter]->nodeTab[2].BC = true;
                    elementTab[counter]->nodeTab[3].BC = true;

                }


            } else {
                if (j == 1) {
                    elementTab[counter]->nodeTab[0].BC = true;
                    elementTab[counter]->nodeTab[1].BC = true;
                    elementTab[counter]->nodeTab[2].BC = true;
                    elementTab[counter]->nodeTab[3].BC = false;
                } else if (j > 1 && j < fileReader.getNh() - 1) {
                    elementTab[counter]->nodeTab[0].BC = false;
                    elementTab[counter]->nodeTab[1].BC = true;
                    elementTab[counter]->nodeTab[2].BC = true;
                    elementTab[counter]->nodeTab[3].BC = false;
                } else {

                    elementTab[counter]->nodeTab[0].BC = false;
                    elementTab[counter]->nodeTab[1].BC = true;
                    elementTab[counter]->nodeTab[2].BC = true;
                    elementTab[counter]->nodeTab[3].BC = true;
                }
            }

            counter++;
        }
    }



    }




void Grid::setValueOfMatrixHAndVectorP() {
    int counter = 0;

    for (int i = 0; i < fileReader.getNh() * fileReader.getNh(); ++i) {
        for (int j = 0; j < fileReader.getNh() * fileReader.getNh() + 1; ++j) {
            if (j == fileReader.getNh() * fileReader.getNh()) {
                matrixHAndVectorP[i][j] = globalVectorP[i];
                continue;
            }

            matrixHAndVectorP[i][j] = globalMatrixH[i][j];
        }
    }

}


void Grid::modifyIndexes(int i, int j, shared_ptr<Element> element) {


    switch (i + 1) {
        case 1:

            modifiedIndexI = element->id[0] - 1;
            break;
        case 2:

            modifiedIndexI = element->id[1] - 1;
            break;
        case 3:

            modifiedIndexI = element->id[2] - 1;
            break;
        case 4:

            modifiedIndexI = element->id[3] - 1;
            break;
        default:

            break;
    }

    switch (j + 1) {
        case 1:
            modifiedIndexJ = element->id[0] - 1;
            break;
        case 2:
            modifiedIndexJ = element->id[1] - 1;
            break;
        case 3:
            modifiedIndexJ = element->id[2] - 1;
            break;
        case 4:
            modifiedIndexJ = element->id[3] - 1;
            break;
        default:
            break;
    }


}
//agregacja macierzy H i C
void Grid::setValueOfGlobalMatrix(shared_ptr<Element> element) {
    double val, val1;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            val = element->matrixH[i][j];
            val1 = element->matrixC[i][j];
            modifyIndexes(i, j, element);
            // cout<<"miejsce w macierzy globalnej"<<modifyIndexI<<" "<<modifyIndexJ;
            globalMatrixC[modifiedIndexI][modifiedIndexJ] += val1;
            globalMatrixH[modifiedIndexI][modifiedIndexJ] += val;

        }


    }


}

void Grid::upgradeVectorP() {
    double val1 = 0;


    for (int j = 0; j < fileReader.getNl() * fileReader.getNh(); ++j) {

        globalVectorP[j] = 0;
        for (int i = 0; i < fileReader.getNl() * fileReader.getNh(); ++i) {

            val1 += ((globalMatrixC[j][i] / fileReader.getSimulationStepTime()) * vectorOfTemperatures[i]);

        }
        //  cout << val1 << "  ";
        // cout << endl;
        globalVectorP[j] = -vectorP[j] + val1;
        val1 = 0;


    }


}

void Grid::setMatrixs() {
    vector<shared_ptr<Matrix>> matrixVec;
    double val1 = 0;
    int i = 0;
    for (vector<shared_ptr<Element >>::iterator iter = elementTab.begin();
         iter != elementTab.end(); iter++) {
        //  cout << "Element nr " << ++i << endl;
        //(*iter)->showId();
       matrixVec.emplace_back(new Matrix(*(iter)));
//
       setValueOfGlobalMatrix(*(iter));
     setValueOfVectorP(*(iter));

    }


    for (int j = 0; j < fileReader.getNl() * fileReader.getNh(); ++j) {
        for (int i = 0; i < fileReader.getNl() * fileReader.getNh(); ++i) {

            globalMatrixH[j][i] += globalMatrixC[j][i] / fileReader.getSimulationStepTime();
        }

    }
    // cout << "globalna macierz P bez dodawania\n";
    //showGlobalVectorP();
    //cout << endl;
    for (int k = 0; k < fileReader.getNl() * fileReader.getNh(); ++k) {
        vectorP[k] = globalVectorP[k];
    }
    for (int j = 0; j < fileReader.getNl() * fileReader.getNh(); ++j) {
        for (int i = 0; i < fileReader.getNl() * fileReader.getNh(); ++i) {

            val1 += ((globalMatrixC[j][i] / fileReader.getSimulationStepTime()) * vectorOfTemperatures[i]);

        }
        //  cout << val1 << "  ";
        // cout << endl;
        globalVectorP[j] = -globalVectorP[j] + val1;
        val1 = 0;


    }


}

void Grid::calculateTemperatures() {
    int n = static_cast<int>(fileReader.getNh() * fileReader.getNh());
    long double max;
    long double min;
    for (int j = 0; j < fileReader.getSimulationTime(); j = j + fileReader.getSimulationStepTime()) {

        setValueOfMatrixHAndVectorP();
        //  cout << "wektor p\n";
        // showGlobalVectorP();
        gaussMethod(n);
        max = *max_element(vectorOfTemperatures.begin(), vectorOfTemperatures.end());
        min = *min_element(vectorOfTemperatures.begin(), vectorOfTemperatures.end());
       cout<<j+fileReader.getSimulationStepTime()<<"s"<<" "<< "minTemp " << fixed << min << " " << "maxTemp " << " " << max << endl;
        upgradeVectorP();
//        setValueOfVectorP();


    }


}

bool Grid::gaussMethod(int n) {
    const double eps = 1e-12;
    int i, j, k;
    double m, s;
    fill(vectorOfTemperatures.begin(), vectorOfTemperatures.end(), 0);
    // eliminacja współczynników

    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (fabs(matrixHAndVectorP[i][i]) < eps) return false;
            m = -matrixHAndVectorP[j][i] / matrixHAndVectorP[i][i];
            for (k = i + 1; k <= n; k++)
                matrixHAndVectorP[j][k] += m * matrixHAndVectorP[i][k];
        }
    }

    // wyliczanie niewiadomych

    for (i = n - 1; i >= 0; i--) {
        s = matrixHAndVectorP[i][n];
        for (j = n - 1; j >= i + 1; j--)
            s -= matrixHAndVectorP[i][j] * vectorOfTemperatures[j];
        if (fabs(matrixHAndVectorP[i][i]) < eps) return false;
        vectorOfTemperatures[i] = s / matrixHAndVectorP[i][i];
    }
    return true;

}

void Grid::setValueOfVectorP(shared_ptr<Element> element) {
    double val, val1 = 0;
    for (int i = 0; i < 4; ++i) {
        val = element->vectorP[i];
        modifyIndexes(i, 0, element);
        // cout<<"indeks w macierzy globalnej "<<modifiedIndexI<<endl;
        globalVectorP[modifiedIndexI] += val;
    }


}

void Grid::showGlobalVectorP() {
    for (int i = 0; i < fileReader.getNl() * fileReader.getNh(); ++i) {
        cout << vectorP[i] << endl;
    }


}

void Grid::showGlobalMatrixH() {
    for (int i = 0; i < fileReader.getNl() * fileReader.getNh(); ++i) {

        for (int j = 0; j < fileReader.getNl() * fileReader.getNh(); ++j) {
            cout << globalMatrixH[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
    for (int i = 0; i < fileReader.getNl() * fileReader.getNh(); ++i) {

        for (int j = 0; j < fileReader.getNl() * fileReader.getNh()-1; ++j) {
            cout << matrixHAndVectorP[i][j] << " ";
        }
        cout << endl;
    }

}

void Grid::showGlobalMatrixC() {
    for (int i = 0; i < fileReader.getNl() * fileReader.getNh(); ++i) {

        for (int j = 0; j < fileReader.getNl() * fileReader.getNh(); ++j) {
            cout << globalMatrixC[i][j] << " ";
        }
        cout << endl;
    }

}