// Includes do C++

#include <math.h>

// Includes da Simulação

#include "Detector.hh"
#include "CampoEletrico.hh"
#include "DetectorSensivel.hh"
#include "DetectorMens.hh"

// Includes de Geometria

#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4MultiUnion.hh"

// Include de Unidades

#include "CLHEP/Units/SystemOfUnits.h"

// Includes do Campo

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4ElectroMagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4UniformElectricField.hh"
#include "G4EqMagElectricField.hh"
#include "G4IntegrationDriver.hh"
#include "G4DormandPrince745.hh"
#include "G4ChordFinder.hh"

using namespace CLHEP;

//Definição das variáveis utilizadas
    
    // NÃO ALTERAR ESSAS VARIÁVEIS

static constexpr double R = 62.3636*L*torr/(kelvin*mole); // Constante universal dos Gases Ideais L.torr/(kelvin.mol)
G4int variaveis = 8; // Número de variáveis para o Integrador de Caminho
G4double passoMin = 0.010*mm; // Passo mínimo utilizado pelo ChordFinder
G4int n = 60; // Número de fios nos Cátodos
static constexpr double mP10 = 19.765946*g/mole; // Massa molar do P10, CH4 10% + Ar 90%
static constexpr double mNe = 20.17*g/mole; // Massa molar do Neônio

    // Dimenções e Variáveis Relevantes

double tamanhomundo = 1*m; // Tamanho da Aresta do Mundo
double densidadenicr = 8.4*g/cm3; // Densidade do Nicrômio
double comprimento = 0.6*m; // Comprimento do Detector
double raio = 30*0.025*mm; // Raio dos fios de Nicrômio
double distcatint = 20.003*mm; // Posição do Cátodo Interno
double distcatext = 96.003*mm; // Posição do Cátodo Externo
double raiofioouro = 2*raio/2; // Raio do Fio de Ouro


Detector::Detector()
    : pressaogas(1*torr),
    intcamp(12500*volt),
    temperaturagas(300*kelvin){

        detectormens = new DetectorMens(this);
}

Detector::~Detector()
{
    delete detectormens;
}

G4VPhysicalVolume* Detector::Construct()
{   
    //Definição dos materiais utilizados

    densidadegas = mNe*pressaogas/(R*temperaturagas); // Densidade do Neônio
    
    auto Aluminio = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
    auto Ouro = G4NistManager::Instance()->FindOrBuildMaterial("G4_Au");
    auto Niquel = G4NistManager::Instance()->FindOrBuildMaterial("G4_Ni");
    auto Cromo = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cr");
    auto Neonio = G4NistManager::Instance()->FindOrBuildMaterial("G4_Ne");
    auto Vacuo = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");

    auto Nicromo = new G4Material("Nichrome", densidadenicr, 2); 
    Nicromo->AddMaterial(Niquel, 77.0*perCent); 
    Nicromo->AddMaterial(Cromo, 23.0*perCent);
    
    auto GasAtivo = new G4Material("Gás de Neônio",densidadegas,Neonio,kStateGas,temperaturagas,pressaogas);

    // Definição do Mundo

    auto mundo = new G4Box("mundo", tamanhomundo, tamanhomundo, tamanhomundo);
    auto mundoLogico = new G4LogicalVolume(mundo, Vacuo, "mundoLogico");
    auto mundoFisico = new G4PVPlacement(0, {0, 0, 0}, mundoLogico, "Mundo", 0, false, 0);

    // Definição do Gás Ativo
    
    auto gasativo = new G4Tubs("gasativo", 0, 10.45*cm, comprimento, 0, twopi);
    auto gasativoLogico = new G4LogicalVolume(gasativo, GasAtivo, "gasativoLogico");
    auto gasativoFisico = new G4PVPlacement(0, {0, 0, 0}, gasativoLogico, "Gás Ativo", mundoLogico, false, 0);
    
    auto fio = new G4Tubs("fio", 0, raio, comprimento, 0, twopi);

    auto catext = new G4MultiUnion("catext");
    
    // Definição do Cátodo Externo

    for (G4int i = 0; i < n; i++) {
        G4RotationMatrix nula = G4RotationMatrix(0, 0, 0);
        G4Tubs* fio = new G4Tubs("fio", 0, raio, comprimento, 0, twopi);
        G4ThreeVector pos = G4ThreeVector(distcatext*cos(i*twopi/60.), distcatext*sin(i*twopi/60.), 0);
        G4Transform3D tr = G4Transform3D(nula, pos);
        catext->AddNode(*fio, tr);
    }

    catext->Voxelize();

    auto catodoextLogico2 = new G4LogicalVolume(catext, Nicromo, "catodoextLogico");
    auto catodoextFisico2 = new G4PVPlacement(0, {0, 0, 0}, catodoextLogico2, "Cátodo Externo", gasativoLogico, false, 0);

    // Definição do Cátodo Interno

    auto catint = new G4MultiUnion("catint");

    for (G4int i = 0; i < n; i++) {
        G4RotationMatrix nula = G4RotationMatrix(0, 0, 0);
        G4Tubs* fio = new G4Tubs("fio", 0, raio, comprimento, 0, twopi);
        G4ThreeVector pos = G4ThreeVector(distcatint*cos(i*twopi/60.), distcatint*sin(i*twopi/60.), 0);
        G4Transform3D tr = G4Transform3D(nula, pos);
        catint->AddNode(*fio, tr);
    }

    catint->Voxelize();

    auto catodointLogico2 = new G4LogicalVolume(catint, Nicromo, "catodointLogico");
    auto catodointFisico2 = new G4PVPlacement(0, {0, 0, 0}, catodointLogico2, "Cátodo Interno", gasativoLogico, false, 0);

    // Definição do Cátodo Externo de Aluminio

    auto tuboext = new G4Tubs("tuboext", 10.5*cm, 10.66*cm, comprimento, 0, twopi); 
    auto tuboextLogico = new G4LogicalVolume(tuboext, Aluminio, "tuboextLogico");
    auto tuboextFisico = new G4PVPlacement(0, {0, 0, 0}, tuboextLogico, "Cátodo Alumínio", mundoLogico, false, 0);

    // Definição do Ânodo de Ouro

    auto fioint = new G4Tubs("fioint", 0, raiofioouro, comprimento, 0, twopi);
    auto fiointLogico = new G4LogicalVolume(fioint, Ouro, "fiointLogico");
    auto fiointFisico = new G4PVPlacement(0, {0,0,0}, fiointLogico, "Ânodo de Ouro", gasativoLogico, false, 0);

    auto sensor1 = new DetectorSensivel("Ânodo de Ouro", ReCampoInt());
    fiointLogico->SetSensitiveDetector(sensor1);
    return mundoFisico;
}

// Construtor do Campo

void Detector::ConstructSDandField(){

    auto campoEletrico = new Campo(intcamp);
    auto campoManager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    auto campoEq = new G4EqMagElectricField(campoEletrico);
    auto passo = new G4DormandPrince745(campoEq, variaveis);
    auto integrador = new G4IntegrationDriver<G4DormandPrince745>(passoMin, passo, variaveis);
    auto caminho = new G4ChordFinder(integrador);

    campoManager->SetDetectorField(campoEletrico);
    campoManager->SetChordFinder(caminho);
}