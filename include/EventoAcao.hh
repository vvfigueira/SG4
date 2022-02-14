#ifndef EventoAcao_h
#define EventoAcao_h 1

#include "RunAcao.hh"

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