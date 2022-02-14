#include "Detector.hh"
#include "InicializadorAcao.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "QBBC.hh"
#include "QGSP_BERT_HP.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

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

    #ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    #else
    G4RunManager* runManager = new G4RunManager;
    #endif

    runManager->SetUserInitialization(new Detector());
    auto factory = new G4PhysListFactory();
    //G4cout << factory->AvailablePhysListsEM();
    auto physicsList = factory->GetReferencePhysList("QBBC_PEN");
    runManager->SetUserInitialization(physicsList);
    physicsList->SetVerboseLevel(0);
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