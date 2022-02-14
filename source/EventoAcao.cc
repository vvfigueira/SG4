#include "EventoAcao.hh"
#include "Analise.hh"

#include "G4Event.hh"

EventoAcao::EventoAcao(RunAcao* runAction)
    : G4UserEventAction(){}

EventoAcao::~EventoAcao(){}

void EventoAcao::BeginOfEventAction(const G4Event* event){

}

void EventoAcao::EndOfEventAction(const G4Event* event){}