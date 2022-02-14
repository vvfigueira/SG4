#ifndef InicializadorAcao_h
#define InicializadorAcao_h 1

#include "G4VUserActionInitialization.hh"

class InicializadorAcao : public G4VUserActionInitialization
{
    public:
        InicializadorAcao();
        virtual ~InicializadorAcao();

        virtual void BuildForMaster() const;
        virtual void Build() const;
};

#endif