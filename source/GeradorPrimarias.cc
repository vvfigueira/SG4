#include "GeradorPrimarias.hh"

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4Geantino.hh"
#include "G4Electron.hh"

GeradorPrimarias::GeradorPrimarias()
    : G4VUserPrimaryGeneratorAction(), 
    mParticleGun( new G4ParticleGun( G4Geantino::Definition() ) ){
        G4ThreeVector pos = G4ThreeVector(0*m, 0.05*m, 0*m);
        //mParticleGun->SetParticleEnergy(200*eV);
        mParticleGun->SetParticlePosition(pos);

}

GeradorPrimarias::~GeradorPrimarias(){}

void GeradorPrimarias::GeneratePrimaries(G4Event* anEvent)
{
    mParticleGun->GeneratePrimaryVertex(anEvent);   
}