#include "DetectorMens.hh"
#include "Detector.hh"

#include "G4UIdirectory.hh"
#include "G4SystemOfUnits.hh"

DetectorMens::DetectorMens(Detector* HPGeDet) : detector(HPGeDet) {

    detectorDir = new G4UIdirectory("/Detector/");
    detectorDir->SetGuidance("Controle de variáveis do Detector");

    DefGasPressaoCmd =
      new G4UIcmdWithADoubleAndUnit("/Detector/DefGasPressao", this);

    DefGasPressaoCmd->SetGuidance("Altera a Pressão do Gás Ativo.");
    DefGasPressaoCmd->SetUnitCategory("Pressure");
    DefGasPressaoCmd->SetDefaultValue(1*torr);
    DefGasPressaoCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    MostrarGasPressaoCmd =
      new G4UIcmdWithoutParameter("/Detector/MostrarGasPressao", this);

    MostrarGasPressaoCmd->SetGuidance("Mostra a Pressão atual do Gás Ativo.");
    MostrarGasPressaoCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    ReGasPressaoCmd =
      new G4UIcmdWithoutParameter("/Detector/ReGasPressao", this);

    ReGasPressaoCmd->SetGuidance("Retorna a Pressão atual do Gás Ativo.");
    ReGasPressaoCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    DefGasTempCmd =
      new G4UIcmdWithADoubleAndUnit("/Detector/DefGasTemp", this);

    DefGasTempCmd->SetGuidance("Altera a Temperatura do Gás Ativo.");
    DefGasTempCmd->SetUnitCategory("Temperature");
    DefGasTempCmd->SetDefaultValue(300*kelvin);
    DefGasTempCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    MostrarGasTempCmd =
      new G4UIcmdWithoutParameter("/Detector/MostrarGasTemp", this);

    MostrarGasTempCmd->SetGuidance("Mostra a Temperatura atual do Gás Ativo.");
    MostrarGasTempCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    ReGasTempCmd =
      new G4UIcmdWithoutParameter("/Detector/ReGasTemp", this);

    ReGasTempCmd->SetGuidance("Retorna a Temperatura atual do Gás Ativo.");
    ReGasTempCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

    DefCampoIntCmd =
      new G4UIcmdWithADoubleAndUnit("/Detector/DefCampoInt", this);

    DefCampoIntCmd->SetGuidance("Altera a Intensidade do Campo.");
    DefCampoIntCmd->SetUnitCategory("Electric potential");
    DefCampoIntCmd->SetDefaultValue(12500*volt);
    DefCampoIntCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    MostrarCampoIntCmd =
      new G4UIcmdWithoutParameter("/Detector/MostrarCampoInt", this);

    MostrarCampoIntCmd->SetGuidance("Mostra a Intensidade atual do Campo.");
    MostrarCampoIntCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    ReCampoIntCmd =
      new G4UIcmdWithoutParameter("/Detector/ReCampoInt", this);

    ReCampoIntCmd->SetGuidance("Retorna a Intensidade atual do Campo.");
    ReCampoIntCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}

DetectorMens::~DetectorMens() {
    delete detectorDir;
}

void DetectorMens::SetNewValue(G4UIcommand* command, G4String newValues) {
    if (command == DefGasPressaoCmd){
        detector->DefGasPressao(DefGasPressaoCmd->GetNewDoubleValue(newValues));
    }
    if(command == MostrarGasPressaoCmd){
        detector->MostrarGasPressao();
    }
    if(command == ReGasPressaoCmd){
        detector->ReGasPressao();
    }

    if(command == DefGasTempCmd){
        detector->DefGasTemp(DefGasTempCmd->GetNewDoubleValue(newValues));
    }
    if(command == MostrarGasTempCmd){
        detector->MostrarGasTemp();
    }
    if(command == ReGasTempCmd){
        detector->ReGasTemp();
    }

    if (command == DefCampoIntCmd){
        detector->DefCampoInt(DefCampoIntCmd->GetNewDoubleValue(newValues));
    }
    if(command == MostrarCampoIntCmd){
        detector->MostrarCampoInt();
    }
    if(command == ReCampoIntCmd){
        detector->ReCampoInt();
    }
}
