#ifndef DetectorMens_h
#define DetectorMens_h 1

#include "Detector.hh"

#include "G4SystemOfUnits.hh"
#include "G4UImessenger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWith3Vector.hh"

class Detector;

class DetectorMens : public G4UImessenger {
    public:
        DetectorMens(Detector*);
        ~DetectorMens();
        
        void SetNewValue(G4UIcommand*, G4String);

    private:
        Detector* detector;

        G4UIdirectory* detectorDir; 

        G4UIcmdWithADoubleAndUnit* DefGasPressaoCmd;
        G4UIcmdWithoutParameter* MostrarGasPressaoCmd;
        G4UIcmdWithoutParameter* ReGasPressaoCmd;
        G4UIcmdWithADoubleAndUnit* DefGasTempCmd;
        G4UIcmdWithoutParameter* MostrarGasTempCmd;
        G4UIcmdWithoutParameter* ReGasTempCmd;
        G4UIcmdWithADoubleAndUnit* DefCampoIntCmd;
        G4UIcmdWithoutParameter* MostrarCampoIntCmd;
        G4UIcmdWithoutParameter* ReCampoIntCmd;
};
#endif