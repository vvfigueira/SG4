// Includes da Simulação

#include "GeradorPrimarias.hh"

// Includes do Geant4

#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include "G4Geantino.hh"

GeradorPrimarias::GeradorPrimarias()
    : G4VUserPrimaryGeneratorAction(), 
    mParticleGun( new G4ParticleGun( G4Geantino::Definition() ) ){
        G4ThreeVector pos = G4ThreeVector(0*m, 0.05*m, 0*m);
        mParticleGun->SetParticlePosition(pos);

}

GeradorPrimarias::~GeradorPrimarias(){}

void GeradorPrimarias::GeneratePrimaries(G4Event* anEvent)
{
    mParticleGun->GeneratePrimaryVertex(anEvent);   
}