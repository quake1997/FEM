//
// Created by new on 2018-10-18.
//

#ifndef UNTITLED2_FILEREADER_H
#define UNTITLED2_FILEREADER_H

#include <iostream>
#include "../libs/json.hpp"
#include <fstream>

#include <string>

//ctrl+alt+l
using namespace std;
using json = nlohmann::json;


class FileReader {

private:
    double H, L, nh, nl;
    string path;
    json params;
public:
FileReader();
   FileReader(string);
    double getH() const;

    void setH(double H);

    double getL() const;

    void setL(double L);

    double getNh() const;

    void setNh(double nh);

    double getNl() const;

    void setNl(double nl);

    void readFromFile();


};


#endif //UNTITLED2_FILEREADER_H
