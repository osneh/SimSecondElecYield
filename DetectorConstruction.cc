#include "DetectorConstruction.hh"
#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction()
{}

DetectorConstruction::~DetectorConstruction()
{}

G4VPhysicalVolume *DetectorConstruction::Construct()
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
    G4LogicalVolume *logicTarget  = new G4LogicalVolume(solidTarget,targetMaterial, "logicTarget");
    //G4VPhysicalVolume *physTarget = new G4PVPlacement(0, G4ThreeVector(0., 0., 200*um), logicTarget,"Target",physWorld,false,0,true);
    G4VPhysicalVolume *physTarget = new G4PVPlacement(0, G4ThreeVector(0., 0., 200*um), "Target", logicTarget,physWorld,false,0,true);


    // Set visualization attributes
    G4VisAttributes* Target_vis = new G4VisAttributes(G4Colour::Yellow());
    logicTarget->SetVisAttributes(Target_vis);

    return physWorld;
}
