//
// Created by new on 2018-10-18.
//

#include <iomanip>
#include "../Header Files/FileReader.h"

FileReader::FileReader() {}

FileReader::FileReader(string path){
    this->path = path;
    shapeFunctionTab = new double *[4];
    for (int i = 0; i < 4; ++i) {
        shapeFunctionTab[i] = new double[4];
    }
  ksiTab = make_unique<double[]>(4);
   etaTab = make_unique<double[]>(4);
   readFromFile();

}

FileReader::~FileReader() {
    for (int i = 0; i < 4; ++i) {
        delete[] shapeFunctionTab[i];
    }
    delete[] shapeFunctionTab;
}

double FileReader::getH() const {
    return H;
}

void FileReader::setH(double H) {
    FileReader::H = H;
}

double FileReader::getL() const {
    return L;
}

void FileReader::setL(double L) {
    FileReader::L = L;
}

double FileReader::getNh() const {
    return nh;
}

void FileReader::setNh(double nh) {
    FileReader::nh = nh;
}

double FileReader::getNl() const {
    return nl;
}

void FileReader::setNl(double nl) {
    FileReader::nl = nl;
}


void FileReader::readFromFile() {


    string point = "point";
    string N = "N";
    string iter;


    try {
        ifstream file(this->path);

        file >> params;

        this->H = (params["H"]); // code may not work if  i don't cast to double
        this->L = (params["L"]);
        this->nh = (params["nh"]);
        this->nl = (params["nl"]);
        this->k=(params["k"]);
        this->c=(params["c"]);
        this->ro=(params["ro"]);
        this->alfa=(params["alfa"]);
        this->initialTemperature=params["initialTemperature"];
        this->ambientTemperature=params["ambientTemperature"];
        this->simulationStepTime=params["simulationStepTime"];
        this->simulationTime=params["simulationTime"];


           //set value of ksi and eta table
       for (int i = 0; i < 4 ; ++i) {
            ksiTab[i]=params["ksiTab"][i]["ksi"+to_string(i+1)];

            etaTab[i]=params["etaTab"][i]["eta"+to_string(i+1)];


        }

           //set value of shapeFunctions
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                shapeFunctionTab[i][j] = params["shapeFunctions"]["point" + to_string(i + 1)][j]["N" +
                                                                                                 to_string(j + 1)];
               // cout << setw(3) << shapeFunctionTab[i][j] << " ";
            }
            //cout << endl;
        }


        for (int k = 0; k < 4 ; ++k) {

           heatingElement.push_back(params["heatingElement"][k]["edge"+to_string(k+1)]);
            //cout<<heatingElement[k]<<endl;
        }



    } catch (exception &e) {
        e.what();
    }


}


const string &FileReader::getPath() const {
    return path;
}

void FileReader::setPath(const string &path) {
    FileReader::path = path;
}

const json &FileReader::getParams() const {
    return params;
}

void FileReader::setParams(const json &params) {
    FileReader::params = params;
}

double **FileReader::getShapeFunctionTab() const {
    return shapeFunctionTab;
}

void FileReader::setShapeFunctionTab(double **shapeFunctionTab) {
    FileReader::shapeFunctionTab = shapeFunctionTab;
}

const unique_ptr<double[]> &FileReader::getKsiTab() const {
    return ksiTab;
}



const unique_ptr<double[]> &FileReader::getEtaTab() const {
    return etaTab;
}

const vector<bool> &FileReader::getHeatingElement() const {
    return heatingElement;
}

double FileReader::getK() const {
    return k;
}

double FileReader::getC() const {
    return c;
}

double FileReader::getRo() const {
    return ro;
}

double FileReader::getAlfa() const {
    return alfa;
}

double FileReader::getInitialTemperature() const {
    return initialTemperature;
}

double FileReader::getAmbientTemperature() const {
    return ambientTemperature;
}

int FileReader::getSimulationTime() const {
    return simulationTime;
}

int FileReader::getSimulationStepTime() const {
    return simulationStepTime;
}
