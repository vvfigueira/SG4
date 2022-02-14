#ifndef TrackAcao_h
#define TrackAcao_h 1

#include "G4UserTrackingAction.hh"
#include "G4Track.hh"
#include "EventoAcao.hh"

class TrackAcao : public G4UserTrackingAction 
{
    public:
        TrackAcao(EventoAcao* eventoacao);
        ~TrackAcao() {};

        virtual void  PreUserTrackingAction(const G4Track*);
        virtual void PostUserTrackingAction(const G4Track*);
};

#endif