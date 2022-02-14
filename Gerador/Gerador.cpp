#include <fstream>

int main(){

    std::ofstream eFile ("Macro.mac" ,std::ofstream::app);

    double pressInit = 0;
    double passoP = 133.322/2;
    int repetP = 25;
    bool Pconst = true;

    double tempInit = 300;
    double passoT = tempInit;
    int repetT = 9;
    bool Tconst = true;

    double campoInit = 12500;
    double passoC = 500;
    int repetC = 25;
    bool Cconst = true;

    double enerInit = 200;
    double passoE = campoInit;
    int repetE = 9;
    bool Econst = true;

    int nPart = 1000000;

    eFile << "/control/verbose 0\n"
          << "/run/verbose 1\n" 
          << "/run/initialize\n\n"
          << "/gun/particle gamma\n"
          << "/gun/position 0 0.05 0 m\n"
          << "/gun/direction 1 0 0\n"
          << "/gun/energy 200 eV\n\n";

    eFile << "/Detector/DefGasTemp " << tempInit << " K\n";
    eFile << "/Detector/DefCampoInt " << campoInit << " V\n\n";
    for(int i = 0; i<= repetP; i++){
        eFile << "/Detector/DefGasPressao " << pressInit+passoP*i << " Pa\n"  
              << "/run/reinitializeGeometry\n"
              << "/run/beamOn " << nPart <<"\n\n";
    }
    eFile.close();

    return 0;
}