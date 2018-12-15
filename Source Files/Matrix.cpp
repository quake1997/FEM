//
// Created by new on 2018-10-31.
//

#include <iomanip>
#include "../Header Files/Matrix.h"

//stworzyc inicjalizacje elmentu
Matrix::Matrix() {

}

Matrix::Matrix(shared_ptr<Element> element) {
    this->element = element;

    fileReader = make_unique<FileReader>("params.json");
    this->c = fileReader->getC();
    this->ro = fileReader->getRo();
    this->alfa = fileReader->getAlfa();
   // this->det = 0.01665;

    derivativeOfShapeFunctionEta = make_unique<unique_ptr<double[]>[]>(4);

    vectorP = make_unique<double[]>(4);


    derivativeOfShapeFunctionKsi = make_unique<unique_ptr<double[]>[]>(4);
    matrixJ = make_unique<unique_ptr<double[]>[]>(4);
    matrixJFinall = make_unique<unique_ptr<double[]>[]>(4);
    detJ = make_unique<double[]>(4);
    derivativeOfShapeFunctionX = make_unique<unique_ptr<double[]>[]>(4);
    derivativeOfShapeFunctionY = make_unique<unique_ptr<double[]>[]>(4);

    multiplicationMatrixForFirstPointX = make_unique<unique_ptr<double[]>[]>(4);
    multiplicationMatrixForSecondPointX = make_unique<unique_ptr<double[]>[]>(4);
    multiplicationMatrixForThirdPointX = make_unique<unique_ptr<double[]>[]>(4);
    multiplicationMatrixForFourthPointX = make_unique<unique_ptr<double[]>[]>(4);

    multiplicationMatrixForFirstPointY = make_unique<unique_ptr<double[]>[]>(4);
    multiplicationMatrixForSecondPointY = make_unique<unique_ptr<double[]>[]>(4);
    multiplicationMatrixForThirdPointY = make_unique<unique_ptr<double[]>[]>(4);
    multiplicationMatrixForFourthPointY = make_unique<unique_ptr<double[]>[]>(4);

    matrixH = make_unique<unique_ptr<double[]>[]>(4);
    matrixC = make_unique<unique_ptr<double[]>[]>(4);


    for (int i = 0; i < 4; i++) {
        tab = make_unique<double[]>(5);
        derivativeOfShapeFunctionKsi[i] = move(tab);
        tab = make_unique<double[]>(5);
        derivativeOfShapeFunctionEta[i] = move(tab);
        tab = make_unique<double[]>(5);
        matrixJ[i] = move(tab);
        tab = make_unique<double[]>(5);
        matrixJFinall[i] = move(tab);
        tab = make_unique<double[]>(5);


        derivativeOfShapeFunctionX[i] = move(tab);
        tab = make_unique<double[]>(5);
        derivativeOfShapeFunctionY[i] = move(tab);
        tab = make_unique<double[]>(5);


        multiplicationMatrixForFirstPointX[i] = move(tab);
        tab = make_unique<double[]>(5);
        multiplicationMatrixForSecondPointX[i] = move(tab);
        tab = make_unique<double[]>(5);
        multiplicationMatrixForThirdPointX[i] = move(tab);
        tab = make_unique<double[]>(5);
        multiplicationMatrixForFourthPointX[i] = move(tab);
        tab = make_unique<double[]>(5);
        multiplicationMatrixForFirstPointY[i] = move(tab);
        tab = make_unique<double[]>(5);
        multiplicationMatrixForSecondPointY[i] = move(tab);
        tab = make_unique<double[]>(5);
        multiplicationMatrixForThirdPointY[i] = move(tab);
        tab = make_unique<double[]>(5);
        multiplicationMatrixForFourthPointY[i] = move(tab);
        tab = make_unique<double[]>(5);
        matrixH[i] = move(tab);
        tab = make_unique<double[]>(5);
        matrixC[i] = move(tab);


    }





    setValueOfDerivativeShapeFunctionEta();
    setValueOfDerivativeShapeFunctionKsi();
    setValueOfMatrixJ();
    setValueOfDetJ();
    setValueOfMatrixJFinall();
    setValueOfDerivativeShapeFunctionY();
    setValueOfDerivativeShapeFunctionX();
    setValueOfMultiplicationMatrix();
    setValueOfMatrixH();
    setValueOfMatrixC();
    element->matrixC = move(matrixC);
    element->matrixH = move(matrixH);
    element->vectorP = move(vectorP);
}

Matrix::~Matrix() {

}

void Matrix::setValueOfDerivativeShapeFunctionEta() {
    int counter;
    double val;

//auto& etaTab=fileReader->getEtaTab();
    for (int i = 0; i < 4; ++i) {
        counter = 0;
        if (i == 2 || i == 3) {
            val = 0.25;
        } else {
            val = -0.25;
        }
        for (int j = 0; j < 4; ++j) {

            if (i == 0 || i == 3) {

                derivativeOfShapeFunctionEta[i][j] = val * (1 - fileReader->getKsiTab()[counter++]);
            } else {
                derivativeOfShapeFunctionEta[i][j] = val * (1 + fileReader->getKsiTab()[counter++]);

            }
            // cout << derivativeOfShapeFunctionEta[i][j] << " " << setw(3);
        }
        //cout << endl;


    }


}

void Matrix::setValueOfDerivativeShapeFunctionKsi() {
    int counter;
    double val;

//auto& etaTab=fileReader->getEtaTab();
    for (int i = 0; i < 4; ++i) {
        counter = 0;
        if (i == 1 || i == 2) {
            val = 0.25;
        } else {
            val = -0.25;
        }
        for (int j = 0; j < 4; ++j) {

            if (i == 2 || i == 3) {

                derivativeOfShapeFunctionKsi[i][j] = val * (1 + fileReader->getEtaTab()[counter++]);
            } else {
                derivativeOfShapeFunctionKsi[i][j] = val * (1 - fileReader->getEtaTab()[counter++]);

            }
            // cout << derivativeOfShapeFunctionKsi[i][j] << " " << setw(3);
        }
        //cout << endl;


    }

}
//odwrocona macierz jakcobiego przeksztalcenia(bez uzglednienia mnozenia przez wyznacznik) dla kazdego z punktow calkowania
void Matrix::setValueOfMatrixJ() {
    int counter = 0;
    double val;
    double val1;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrixJ[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                if (i == 0) {
                    val = element->nodeTab[counter].x;

                    val1 = derivativeOfShapeFunctionKsi[counter][j];
                } else if (i == 1) {
                    val = element->nodeTab[counter].y;
                    val1 = derivativeOfShapeFunctionKsi[counter][j];
                } else if (i == 2) {
                    val = element->nodeTab[counter].x;
                    val1 = derivativeOfShapeFunctionEta[counter][j];

                } else {
                    val = element->nodeTab[counter].y;
                    val1 = derivativeOfShapeFunctionEta[counter][j];
                }
                matrixJ[i][j] += val1 * val;
                // cout <<  derivativeOfShapeFunctionKsi[counter][j] << endl;
                counter++;
            }

            counter = 0;
            // cout << matrixJ[i][j];
        }
        //   cout << endl;
    }

}
//wyznacznik macierzy jacoebiego dla danego punkty czyli jacobian
void Matrix::setValueOfDetJ() {


    detJ[0] = (matrixJ[0][0] * matrixJ[3][0] - (matrixJ[2][0] * matrixJ[1][0]));
    detJ[1] = (matrixJ[0][1] * matrixJ[3][1] - (matrixJ[2][1] * matrixJ[1][1]));
    detJ[2] = (matrixJ[0][2] * matrixJ[3][2] - (matrixJ[2][2] * matrixJ[1][2]));
    detJ[3] = (matrixJ[0][3] * matrixJ[3][3] - (matrixJ[2][3] * matrixJ[1][3]));

//    for (int i = 0; i < 4; ++i) {
//        cout<<detJ[i]<<endl;
//    }


}
//macierz J finalna
void Matrix::setValueOfMatrixJFinall() {
    int index;

    for (int i = 0; i < 4; ++i) {
        if (i == 0) {
            index = 3;


        } else if (i == 1) {
            index = 1;

        } else if (i == 2) {
            index++;

        } else {
            index = 0;

        }
        for (int j = 0; j < 4; ++j) {
            if (i == 1) {
                matrixJFinall[i][j] = ((-1) * (matrixJ[index][j] / detJ[j]));
                // continue;
            } else {
                matrixJFinall[i][j] = (matrixJ[index][j] / detJ[j]);
            }


            // cout << matrixJFinall[i][j];
        }

        //  cout << endl;
    }


}

void Matrix::setValueOfDerivativeShapeFunctionX() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            derivativeOfShapeFunctionX[i][j] = (matrixJFinall[0][i] * derivativeOfShapeFunctionKsi[j][i]) +
                                               (matrixJFinall[1][i] * derivativeOfShapeFunctionEta[j][i]);
            //   cout << derivativeOfShapeFunctionX[i][j] << " " << setw(3);
        }
        // cout << endl;
    }

}


void Matrix::setValueOfDerivativeShapeFunctionY() {

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            derivativeOfShapeFunctionY[i][j] = (matrixJFinall[2][i] * derivativeOfShapeFunctionKsi[j][i]) +
                                               (matrixJFinall[3][i] * derivativeOfShapeFunctionEta[j][i]);
            //  cout << derivativeOfShapeFunctionY[i][j] << " " << setw(3);

        }

        //cout << endl;
    }

}

void Matrix::setValueOfMultiplicationMatrix() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {


            multiplicationMatrixForFirstPointX[i][j] =
                    (derivativeOfShapeFunctionX[0][j] * derivativeOfShapeFunctionX[0][i]) * detJ[0];
            multiplicationMatrixForSecondPointX[i][j] =
                    (derivativeOfShapeFunctionX[1][j] * derivativeOfShapeFunctionX[1][i]) * detJ[1];
            multiplicationMatrixForThirdPointX[i][j] =
                    (derivativeOfShapeFunctionX[2][j] * derivativeOfShapeFunctionX[2][i]) * detJ[2];
            multiplicationMatrixForFourthPointX[i][j] =
                    (derivativeOfShapeFunctionX[3][j] * derivativeOfShapeFunctionX[3][i]) * detJ[3];

            multiplicationMatrixForFirstPointY[i][j] =
                    (derivativeOfShapeFunctionY[0][j] * derivativeOfShapeFunctionY[0][i]) * detJ[0];
            multiplicationMatrixForSecondPointY[i][j] =
                    (derivativeOfShapeFunctionY[1][j] * derivativeOfShapeFunctionY[1][i]) * detJ[1];
            multiplicationMatrixForThirdPointY[i][j] =
                    (derivativeOfShapeFunctionY[2][j] * derivativeOfShapeFunctionY[2][i]) * detJ[2];
            multiplicationMatrixForFourthPointY[i][j] =
                    (derivativeOfShapeFunctionY[3][j] * derivativeOfShapeFunctionY[3][i]) * detJ[3];


            //    cout << multiplicationMatrixForFourthPointX[i][j] << " " << setw(3);
        }

        //  cout << endl;

    }


}

void Matrix::setValueOfMatrixH() {
//tablica zawierajaca funkcje ksztaltu dla dodatkowych punktow elementu uniwersalnego
    unique_ptr<unique_ptr<double[]>[]> localTabOfShapeFunctions = make_unique<unique_ptr<double[]>[]>(8);
    int counter = 0;
    double sum = 0;
  // this->det=sqrt(pow(element->nodeTab[1].x-element->nodeTab[0].x,2)+pow(element->nodeTab[1].y-element->nodeTab[0].y,2))/2;

    //cout<<"wyznaczik"<<det<<endl;

    unique_ptr<unique_ptr<double[]>[]> matrix1 = make_unique<unique_ptr<double[]>[]>(4);
    unique_ptr<unique_ptr<double[]>[]> matrix2 = make_unique<unique_ptr<double[]>[]>(4);
    unique_ptr<unique_ptr<double[]>[]> matrix3 = make_unique<unique_ptr<double[]>[]>(4);
    unique_ptr<unique_ptr<double[]>[]> matrix4 = make_unique<unique_ptr<double[]>[]>(4);
    unique_ptr<unique_ptr<double[]>[]> matrixForVectorsP = make_unique<unique_ptr<double[]>[]>(4);

    unique_ptr<unique_ptr<double[]>[]> matrixHForBoundaryConditions = make_unique<unique_ptr<double[]>[]>(4);
    unique_ptr<double[]> tab1;

    int index1, index2;
    for (int k = 0; k < 8; ++k) {
        tab = make_unique<double[]>(4);
        localTabOfShapeFunctions[k] = move(tab);


    }
    for (int i = 0; i < 4; i++) {
        tab = make_unique<double[]>(4);
        matrix1[i] = move(tab);
        tab = make_unique<double[]>(4);
        matrix2[i] = move(tab);
        tab = make_unique<double[]>(4);
        matrix3[i] = move(tab);
        tab = make_unique<double[]>(4);
        matrix4[i] = move(tab);
        tab = make_unique<double[]>(4);
        matrixHForBoundaryConditions[i] = move(tab);
        tab = make_unique<double[]>(4);
        matrixForVectorsP[i] = move(tab);


    }

    for (int i = 0; i < 8; ++i) {
        shapeFunction.setN1(universalElement.coordinatesOfUniversalElement[i].x,
                            universalElement.coordinatesOfUniversalElement[i].y);
        shapeFunction.setN2(universalElement.coordinatesOfUniversalElement[i].x,
                            universalElement.coordinatesOfUniversalElement[i].y);
        shapeFunction.setN3(universalElement.coordinatesOfUniversalElement[i].x,
                            universalElement.coordinatesOfUniversalElement[i].y);
        shapeFunction.setN4(universalElement.coordinatesOfUniversalElement[i].x,
                            universalElement.coordinatesOfUniversalElement[i].y);
        localTabOfShapeFunctions[i][0] = shapeFunction.getN1();
        localTabOfShapeFunctions[i][1] = shapeFunction.getN2();
        localTabOfShapeFunctions[i][2] = shapeFunction.getN3();
        localTabOfShapeFunctions[i][3] = shapeFunction.getN4();


    }

    //obliczmy macierz vektorow P dla kazdych z dwoch punktow danej krawedzi
    for (int n = 0; n < 8; ++n) {
        if(counter==3){
            det=sqrt(pow(element->nodeTab[counter].x-element->nodeTab[0].x,2)+pow(element->nodeTab[counter].y-element->nodeTab[0].y,2))/2;

        }
        else{
            det=sqrt(pow(element->nodeTab[counter+1].x-element->nodeTab[counter].x,2)+pow(element->nodeTab[counter+1].y-element->nodeTab[counter].y,2))/2;
        }


        matrixForVectorsP[counter][0] = localTabOfShapeFunctions[n][0] * (-alfa) * det * fileReader->getAmbientTemperature() +
                                        localTabOfShapeFunctions[n + 1][0] * (- alfa) * det *  fileReader->getAmbientTemperature();
        matrixForVectorsP[counter][1] = localTabOfShapeFunctions[n][1] * (- alfa) * det *  fileReader->getAmbientTemperature() +
                                        localTabOfShapeFunctions[n + 1][1] * (-alfa) * det *  fileReader->getAmbientTemperature();
        matrixForVectorsP[counter][2] = localTabOfShapeFunctions[n][2] * (- alfa) * det *  fileReader->getAmbientTemperature() +
                                        localTabOfShapeFunctions[n + 1][2] * (- alfa) * det * fileReader->getAmbientTemperature();
        matrixForVectorsP[counter][3] = localTabOfShapeFunctions[n][3] * (- alfa) * det * fileReader->getAmbientTemperature() +
                                        localTabOfShapeFunctions[n + 1][3] * (- alfa) * det * fileReader->getAmbientTemperature();

        ++n;

        ++counter;

    }


   //wektor P
    for (int i = 0; i < 4; ++i) {


            sum += matrixForVectorsP[0][i]*(element->nodeTab[0].BC & element->nodeTab[1].BC)+
                    matrixForVectorsP[1][i]*(element->nodeTab[1].BC & element->nodeTab[2].BC)+
                    matrixForVectorsP[2][i]*(element->nodeTab[2].BC & element->nodeTab[3].BC)+
                    matrixForVectorsP[3][i]*(element->nodeTab[3].BC & element->nodeTab[0].BC);

        vectorP[i] = sum;


        sum = 0;


    }



    //sumujemy macierze dla obliczonych warunkow brzegowych
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix1[i][j] = ((localTabOfShapeFunctions[0][j] * localTabOfShapeFunctions[0][i] * alfa) +
                             (localTabOfShapeFunctions[1][j] * localTabOfShapeFunctions[1][i] * alfa)) * det;
            matrix2[i][j] = ((localTabOfShapeFunctions[2][j] * localTabOfShapeFunctions[2][i] * alfa) +
                             (localTabOfShapeFunctions[3][j] * localTabOfShapeFunctions[3][i] * alfa)) * det;
            matrix3[i][j] = ((localTabOfShapeFunctions[4][j] * localTabOfShapeFunctions[4][i] * alfa) +
                             (localTabOfShapeFunctions[5][j] * localTabOfShapeFunctions[5][i] * alfa)) * det;
            matrix4[i][j] = ((localTabOfShapeFunctions[6][j] * localTabOfShapeFunctions[6][i] * alfa) +
                             (localTabOfShapeFunctions[7][j] * localTabOfShapeFunctions[7][i] * alfa)) * det;

            matrixHForBoundaryConditions[i][j] = (element->nodeTab[0].BC & element->nodeTab[1].BC) * matrix1[i][j] +
                                                 (element->nodeTab[1].BC & element->nodeTab[2].BC) * matrix2[i][j] +
                                                 (element->nodeTab[2].BC & element->nodeTab[3].BC) * matrix3[i][j] +
                                                 (element->nodeTab[3].BC & element->nodeTab[0].BC) * matrix4[i][j];


        }

    }

//macierz H po dV
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrixH[i][j] = element->k *
                            ((multiplicationMatrixForFirstPointX[i][j] + multiplicationMatrixForFirstPointY[i][j]) +
                             (multiplicationMatrixForSecondPointX[i][j] +
                              multiplicationMatrixForSecondPointY[i][j]) +
                             (multiplicationMatrixForThirdPointX[i][j] + multiplicationMatrixForThirdPointY[i][j]) +
                             (multiplicationMatrixForFourthPointX[i][j] +
                              multiplicationMatrixForFourthPointY[i][j]));

            //dodajemy macierz H dla punktow calkowanie do macierzy H dla warunkow brzegowych
            matrixH[i][j] += matrixHForBoundaryConditions[i][j];


        }


    }


}


void Matrix::setValueOfMatrixC() {
    unique_ptr<unique_ptr<double[]>[]> matrix1 = make_unique<unique_ptr<double[]>[]>(4);
    unique_ptr<unique_ptr<double[]>[]> matrix2 = make_unique<unique_ptr<double[]>[]>(4);
    unique_ptr<unique_ptr<double[]>[]> matrix3 = make_unique<unique_ptr<double[]>[]>(4);
    unique_ptr<unique_ptr<double[]>[]> matrix4 = make_unique<unique_ptr<double[]>[]>(4);
    unique_ptr<double[]> tab1;
    for (int i = 0; i < 4; i++) {
        tab1 = make_unique<double[]>(5);
        matrix1[i] = move(tab1);
        tab1 = make_unique<double[]>(5);
        matrix2[i] = move(tab1);
        tab1 = make_unique<double[]>(5);
        matrix3[i] = move(tab1);
        tab1 = make_unique<double[]>(5);
        matrix4[i] = move(tab1);

    }

    for (int i = 0; i < 4; ++i) {

        for (int j = 0; j < 4; ++j) {
            matrix1[i][j] =
                    shapeFunction.shapeFunctionsTab[0][j] * shapeFunction.shapeFunctionsTab[0][i] * detJ[0] * c * ro;
            matrix2[i][j] =
                    shapeFunction.shapeFunctionsTab[1][j] * shapeFunction.shapeFunctionsTab[1][i] * detJ[1] * c * ro;
            matrix3[i][j] =
                    shapeFunction.shapeFunctionsTab[2][j] * shapeFunction.shapeFunctionsTab[2][i] * detJ[2] * c * ro;
            matrix4[i][j] =
                    shapeFunction.shapeFunctionsTab[3][j] * shapeFunction.shapeFunctionsTab[3][i] * detJ[3] * c * ro;
            matrixC[i][j] = matrix1[i][j] + matrix2[i][j] + matrix3[i][j] + matrix4[i][j];



        }


    }


}

const unique_ptr<FileReader> &Matrix::getFileReader() const {
    return fileReader;
}
