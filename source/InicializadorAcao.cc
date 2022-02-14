#include "InicializadorAcao.hh"
#include "GeradorPrimarias.hh"
#include "EventoAcao.hh"
#include "TrackAcao.hh"
#include "RunAcao.hh"

InicializadorAcao::InicializadorAcao()
 : G4VUserActionInitialization(){}

InicializadorAcao::~InicializadorAcao(){}

void InicializadorAcao::BuildForMaster() const
{
    RunAcao* runacao = new RunAcao;
    SetUserAction(runacao);
}

void InicializadorAcao::Build() const
{
  
    SetUserAction(new GeradorPrimarias);

    RunAcao* runacao = new RunAcao;
    SetUserAction(runacao);

    EventoAcao* eventoacao = new EventoAcao(runacao);
    SetUserAction(eventoacao);

    TrackAcao* trackacao = new TrackAcao(eventoacao);
    SetUserAction(trackacao);

}