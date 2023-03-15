#include<iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"


int main(int argc, char** argv)
{

    G4RunManager *runManager = new G4RunManager();

    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new ActionInitialization());

    runManager->Initialize();
    
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager *UImanager =  G4UImanager::GetUIpointer();

    UImanager->ApplyCommand("/vis/open OGL");
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 1 1 1");
    //UImanager->ApplyCommand("/control/verbose 2");
    //UImanager->ApplyCommand("/control/saveHistory");
    //UImanager->ApplyCommand("/run/verbose 2");
    UImanager->ApplyCommand("/vis/drawVolume");
    
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh /true");
    UImanager->ApplyCommand("/vis/scene/add/trajectoires /smooth");

    UImanager->ApplyCommand("/vis/modeling/trajectories/create/drawByCharge");
    UImanager->ApplyCommand("/vis/modeling/trajectories/drawByCharge-0/default/setDrawStepPts true");


    UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");
    
    //UImanager->ApplyCommand("/vis/reviewKeptEvents");
    
    ui->SessionStart();

    return 0;
}
