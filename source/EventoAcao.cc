// Includes da Simulação

#include "EventoAcao.hh"
#include "Analise.hh"

// Includes do Geant4

#include "G4Event.hh"

EventoAcao::EventoAcao(RunAcao* runAction)
    : G4UserEventAction(){}

EventoAcao::~EventoAcao(){}

void EventoAcao::BeginOfEventAction(const G4Event* event){

}

void EventoAcao::EndOfEventAction(const G4Event* event){}