#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{

    G4NistManager *nist = G4NistManager::Instance();


    // World
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");
    G4Box *solidWorld = new G4Box("World",500.*um,500*um,500.*um);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld,worldMat,"World");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.), logicWorld, "World",0,false, 0, true);

    // Target
    G4Material *targetMaterial = nist->FindOrBuildMaterial("G4_Cu");
    G4Box *solidTarget = new G4Box("Target",400.*um, 400.*um, 40.*um);
    G4LogicalVolume *logicTarget  = new G4LogicalVolume(solidTarget,targetMaterial, "Target");
    G4VPhysicalVolume *physTarget  = new G4PVPlacement(0, G4ThreeVector(0., 0., 200*um), "Target", logicTarget,physWorld,false,0,true);

    return physWorld;

}
