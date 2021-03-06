// Includes do C++

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

// Includes da Simulação

#include "DetectorSensivel.hh"
#include "DetectorMens.hh"
#include "Detector.hh"

// Includes do Geant4

#include "G4VProcess.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include "G4Track.hh"
#include "G4StepStatus.hh"

DetectorSensivel::DetectorSensivel(const G4String &name,G4double intensidade) 
    : G4VSensitiveDetector(name),
    campoInt(intensidade){}

DetectorSensivel::~DetectorSensivel(){}

G4bool DetectorSensivel::ProcessHits(G4Step*aStep, G4TouchableHistory*ROhist){
    
    //auto analiseManager = G4AnalysisManager::Instance();

    pName = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
    energia = aStep->GetPreStepPoint()->GetKineticEnergy();
    nVol = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();
    pressao = aStep->GetTrack()->GetVolume()->GetMotherLogical()->GetMaterial()->GetPressure();
    
    electron = "e-";
    ouro = "Ânodo de Ouro";
    gas = "Gás Ativo";
    
    std::stringstream valorpress;
    valorpress << pressao/torr;
    std::string presscorrig;
    valorpress >> presscorrig;

    std::stringstream valorint;
    valorint << campoInt/volt;
    std::string intcorrig;
    valorint >> intcorrig;
    
    std::ofstream aFile (presscorrig+"torr.txt",std::ofstream::app);
    std::ofstream bFile (intcorrig+"V.txt", std::ofstream::app);
    std::ofstream dFile (presscorrig+"torr"+intcorrig+"V.txt", std::ofstream::app);
    std::ofstream cFile ("Histo2D.txt", std::ofstream::app);
    if (pName == "e-" && nVol == ouro){
        aFile << energia/CLHEP::eV << "\n";
        bFile << energia/CLHEP::eV << "\n";
        dFile << energia/CLHEP::eV << "\n";
        cFile << energia/CLHEP::eV << "\t"
        << pressao/torr << "\n";
        //analiseManager->FillH1(0, energia);
        aStep->GetPreStepPoint()->SetKineticEnergy(0*CLHEP::eV);
    };

    return 0;
}