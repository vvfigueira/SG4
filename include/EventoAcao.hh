#ifndef EventoAcao_h
#define EventoAcao_h 1

// Includes da Simulação

#include "RunAcao.hh"

// Includes do Geant4

#include "G4UserEventAction.hh"
#include "globals.hh"

class EventoAcao : public G4UserEventAction
{
    public:
        
        EventoAcao(RunAcao* runAction);
        virtual ~EventoAcao();

        virtual void  BeginOfEventAction(const G4Event*);
        virtual void    EndOfEventAction(const G4Event*);
};

#endif