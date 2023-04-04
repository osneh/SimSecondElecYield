#ifndef PHYSICSLIST_HH
#define PHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "globals.hh"

class G4VPhysicsConstructor;
class PhysicsListMessenger;

class PhysicsList :  public G4VModularPhysicsList
{
public:
	PhysicsList();
	~PhysicsList() override;

	void ConstructParticle() override;
        
  	void AddPhysicsList(const G4String& name);
    
  	void ConstructProcess() override;    
  	void AddStepMax();
    
private:

  PhysicsListMessenger* fMessenger; 

  G4String fEmName;
  G4VPhysicsConstructor*  fEmPhysicsList;
  G4VPhysicsConstructor*  fDecayPhysics;
  G4VPhysicsConstructor*  fHadPhysicsList;
};


#endif
