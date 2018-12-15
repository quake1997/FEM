//
// Created by new on 2018-10-18.
//

#ifndef UNTITLED2_FILEREADER_H
#define UNTITLED2_FILEREADER_H

#include <iostream>
#include "../libs/json.hpp"
#include <fstream>
#include <memory>
#include <vector>
#include <string>

//ctrl+alt+l
using namespace std;
using json = nlohmann::json;


class FileReader {

private:

    double H, L, nh, nl,k,c,ro,alfa,initialTemperature,ambientTemperature;
    int simulationTime,simulationStepTime;
    unique_ptr<double[]>ksiTab;
    unique_ptr<double[]>etaTab;
    double**shapeFunctionTab;
    vector<bool>heatingElement;
    string path;
    json params;
public:
    const vector<bool> &getHeatingElement() const;

public:
    FileReader();


    FileReader(string);
    ~FileReader();

    const unique_ptr<double[]> &getKsiTab() const;

    double getInitialTemperature() const;

    double getAmbientTemperature() const;

    int getSimulationTime() const;

    int getSimulationStepTime() const;


    const unique_ptr<double[]> &getEtaTab() const;



    double **getShapeFunctionTab() const;

    void setShapeFunctionTab(double **shapeFunctionTab);

    double getK() const;

    double getC() const;

    double getRo() const;

    double getAlfa() const;

    double getH() const;

    void setH(double H);

    double getL() const;

    void setL(double L);

    double getNh() const;

    void setNh(double nh);

    double getNl() const;

    void setNl(double nl);

    void readFromFile();



    const string &getPath() const;

    void setPath(const string &path);

    const json &getParams() const;

    void setParams(const json &params);

};


#endif //UNTITLED2_FILEREADER_H
