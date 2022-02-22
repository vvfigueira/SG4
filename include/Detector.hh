#ifndef Detector_h
#define Detector_h 1

// Includes da Simulação

#include "DetectorMens.hh"

// Includes do Geant4

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

static constexpr double torr = atmosphere/760.;

class DetectorMens;

class Detector : public G4VUserDetectorConstruction
{
    public:
        Detector();
        virtual ~Detector();

        inline void DefGasPressao(G4double d){pressaogas = d;};
        inline void MostrarGasPressao(){G4cout<<"A Pressão é: "
            <<G4BestUnit(pressaogas, "Pressure")<<G4endl;};
        inline double ReGasPressao(){return pressaogas;};

        inline void DefGasTemp(G4double d){temperaturagas = d;};
        inline void MostrarGasTemp(){G4cout<<"A Temperatura é: "
            <<G4BestUnit(temperaturagas, "Temperature")<<G4endl;};
        inline double ReGasTemp(){return temperaturagas;};
        
        inline void DefCampoInt(G4double d){intcamp = d;};
        inline void MostrarCampoInt(){G4cout<<"Potencial base: "
            <<G4BestUnit(intcamp, "Electric potential")<<G4endl;}
        inline double ReCampoInt(){return intcamp;};

        virtual void ConstructSDandField();

        virtual G4VPhysicalVolume* Construct() override;

    private:

        DetectorMens* detectormens;

        G4double intcamp, temperaturagas, pressaogas, densidadegas;

};

#endif