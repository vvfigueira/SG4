#include "CampoEletrico.hh"

#include "CLHEP/Units/SystemOfUnits.h"
#include "math.h"
#include "globals.hh"

using namespace CLHEP;

// Definindo a Classe Campo como Campo Elétrico

Campo::Campo(G4double intcamp)
    : Intensidade3(intcamp){

}

Campo::~Campo(){
    
}

G4bool Campo::DoesFieldChangeEnergy() const{
    return true;
}

// Definição da Classe Campo

void Campo::GetFieldValue(const G4double Point[4], G4double field[6]) const{

    field[0]=0.*tesla;
    field[1]=0.*tesla;
    field[2]=0.*tesla;
    field[5]=0.*volt/mm;
    
    if(sqrt( Point[0]*Point[0]*mm2 + Point[1]*Point[1]*mm2) <= 16.0*cm /*&& sqrt( Point[0]*Point[0]*mm2 + Point[1]*Point[1]*mm2  ) > 96*mm*/){    
        field[3]=Intensidade3*(Point[0]/(Point[0]*Point[0]+Point[1]*Point[1]));
        field[4]=Intensidade3*(Point[1]/(Point[0]*Point[0]+Point[1]*Point[1]));
    }/*else if (sqrt( Point[0]*Point[0]*mm2 + Point[1]*Point[1]*mm2  ) <= 96*mm && sqrt( Point[0]*Point[0]*mm2 + Point[1]*Point[1]*mm2  ) >= 20*mm){
        field[3]=Intensidade2*(Point[0]/sqrt(Point[0]*Point[0]+Point[1]*Point[1]));
        field[4]=Intensidade2*(Point[1]/sqrt(Point[0]*Point[0]+Point[1]*Point[1]));
    }else if (sqrt( Point[0]*Point[0]*mm2 + Point[1]*Point[1]*mm2  ) <= 20*mm){
        field[3]=Intensidade3*(Point[0]/sqrt(Point[0]*Point[0]+Point[1]*Point[1]));
        field[4]=Intensidade3*(Point[1]/sqrt(Point[0]*Point[0]+Point[1]*Point[1]));
    }else{
        field[3]=0.*volt/mm;
        field[4]=0.*volt/mm;
    };*/
}