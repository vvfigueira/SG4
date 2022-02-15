// Includes da Simulação

#include "Detector.hh"
#include "InicializadorAcao.hh"

// Include do Gerenciador

#include "G4RunManager.hh"
#include "G4UImanager.hh"

// Includes de Listas de Física

#include "FTFP_BERT.hh"
#include "QBBC.hh"
#include "QGSP_BERT_HP.hh"

// Includes de Motor de Visualização

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

// Includes adicionais

#include "Randomize.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4PenelopeComptonModel.hh"
#include "G4ComptonScattering.hh"
#include "G4PenelopeIonisationModel.hh"
#include "G4eIonisation.hh"
#include "G4PhysListFactory.hh"

int main(int argc,char** argv)
{

    G4UIExecutive* ui = 0;
    if ( argc == 1 ) {
        ui = new G4UIExecutive(argc, argv);
    }

    CLHEP::RanluxEngine defaultEngine( 1234567, 4 );
    G4Random::setTheEngine( &defaultEngine );
    G4int seed = time( NULL );
    G4Random::setTheSeed( seed );

    G4RunManager* runManager = new G4RunManager;
    runManager->SetUserInitialization(new Detector());

    auto factory = new G4PhysListFactory();
    auto physicsList = factory->GetReferencePhysList("QBBC_PEN");
    physicsList->SetVerboseLevel(0);

    runManager->SetUserInitialization(physicsList);
    runManager->SetUserInitialization(new InicializadorAcao());

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if ( ! ui ) {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }
    else {
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete runManager;
}