#include "RunAcao.hh"
#include "GeradorPrimarias.hh"
#include "Detector.hh"
//#include "Analise.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

RunAcao::RunAcao()
: G4UserRunAction(){}

RunAcao::~RunAcao(){}

void RunAcao::BeginOfRunAction(const G4Run* run)
{
    /*auto analiseManager = G4AnalysisManager::Instance();
    analiseManager->SetVerboseLevel(1);

    int runa = run->GetRunID();

    std::stringstream runid;
    runid << runa;
    std::string runId;
    runid >> runId;

    analiseManager->OpenFile("EletronsAnodo");
    if(analiseManager->GetNofH1s() == 0){
        analiseManager->CreateH1("Energia", "Elétrons no Ânodo",100,0., 50*keV, "eV");
    }*/
}

void RunAcao::EndOfRunAction(const G4Run* run)
{
    /*auto analiseManager = G4AnalysisManager::Instance();
    
    analiseManager->Write();
    analiseManager->CloseFile();*/
}