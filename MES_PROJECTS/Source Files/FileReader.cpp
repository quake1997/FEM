//
// Created by new on 2018-10-18.
//

#include "../Header Files/FileReader.h"
FileReader::FileReader() {}
FileReader::FileReader(string path ) {
    this->path=path;
//dtdty
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





    try {
        ifstream file(this->path);

         file>>params;

         this->H= static_cast<double>(params["H"]);
        this->L= static_cast<double>(params["L"]);
        this->nh= static_cast<double>(params["nh"]);
        this->nl= static_cast<double>(params["nl"]);



    }catch(exception&e){
        e.what();
    }





}