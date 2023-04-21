#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"


DetectorMessenger::DetectorMessenger(DetectorConstruction * Det)
:G4UImessenger(),fDetector(Det),
 fTestemDir(0),
 fDetDir(0),
 fAbsMaterCmd(0),
 fAbsThickCmd(0),
 fAbsSizXYCmd(0),
 fAbsXposCmd(0),
 fWorldMaterCmd(0),
 fWorldXCmd(0),
 fWorldYCmd(0),
 fWorldZCmd(0)
{ 
  fTestemDir = new G4UIdirectory("/testem/");
  fTestemDir->SetGuidance("UI commands specific to this example.");
  
  fDetDir = new G4UIdirectory("/testem/det/");
  fDetDir->SetGuidance("detector construction commands");
      
  fAbsMaterCmd = new G4UIcmdWithAString("/testem/det/setAbsMat",this);
  fAbsMaterCmd->SetGuidance("Select Material of the Absorber.");
  fAbsMaterCmd->SetParameterName("choice",false);
  fAbsMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fAbsMaterCmd->SetToBeBroadcasted(false);
  
  fWorldMaterCmd = new G4UIcmdWithAString("/testem/det/setWorldMat",this);
  fWorldMaterCmd->SetGuidance("Select Material of the World.");
  fWorldMaterCmd->SetParameterName("wchoice",false);
  fWorldMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fWorldMaterCmd->SetToBeBroadcasted(false);
    
  fAbsThickCmd = new G4UIcmdWithADoubleAndUnit("/testem/det/setAbsThick",this);
  fAbsThickCmd->SetGuidance("Set Thickness of the Absorber");
  fAbsThickCmd->SetParameterName("SizeZ",false);  
  fAbsThickCmd->SetRange("SizeZ>0.");
  fAbsThickCmd->SetUnitCategory("Length");  
  fAbsThickCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fAbsThickCmd->SetToBeBroadcasted(false);
  
  fAbsSizXYCmd = new G4UIcmdWithADoubleAndUnit("/testem/det/setAbsXY",this);
  fAbsSizXYCmd->SetGuidance("Set sizeXY of the Absorber");
  fAbsSizXYCmd->SetParameterName("SizeXY",false);
  fAbsSizXYCmd->SetRange("SizeXY>0.");
  fAbsSizXYCmd->SetUnitCategory("Length");
  fAbsSizXYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fAbsSizXYCmd->SetToBeBroadcasted(false);
  
  fAbsXposCmd = new G4UIcmdWithADoubleAndUnit("/testem/det/setAbsXpos",this);
  fAbsXposCmd->SetGuidance("Set X pos. of the Absorber");
  fAbsXposCmd->SetParameterName("Xpos",false);
  fAbsXposCmd->SetUnitCategory("Length");
  fAbsXposCmd->AvailableForStates(G4State_PreInit);
  fAbsXposCmd->SetToBeBroadcasted(false);
  
  fWorldXCmd = new G4UIcmdWithADoubleAndUnit("/testem/det/setWorldX",this);
  fWorldXCmd->SetGuidance("Set X size of the World");
  fWorldXCmd->SetParameterName("WSizeX",false);
  fWorldXCmd->SetRange("WSizeX>0.");
  fWorldXCmd->SetUnitCategory("Length");
  fWorldXCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fWorldXCmd->SetToBeBroadcasted(false);
  
  fWorldYCmd = new G4UIcmdWithADoubleAndUnit("/testem/det/setWorldY",this);
  fWorldYCmd->SetGuidance("Set sizeY of the World");
  fWorldYCmd->SetParameterName("WSizeY",false);
  fWorldYCmd->SetRange("WSizeY>0.");
  fWorldYCmd->SetUnitCategory("Length");
  fWorldYCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fWorldYCmd->SetToBeBroadcasted(false);

  fWorldZCmd = new G4UIcmdWithADoubleAndUnit("/testem/det/setWorldZ",this);
  fWorldZCmd->SetGuidance("Set sizeZ of the World");
  fWorldZCmd->SetParameterName("WSizeZ",false);
  fWorldZCmd->SetRange("WSizeZ>0.");
  fWorldZCmd->SetUnitCategory("Length");
  fWorldZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fWorldZCmd->SetToBeBroadcasted(false);

}

DetectorMessenger::~DetectorMessenger()
{
  delete fAbsMaterCmd; 
  delete fAbsThickCmd; 
  delete fAbsSizXYCmd;  
  delete fAbsXposCmd; 
  delete fWorldMaterCmd;
  delete fWorldXCmd;
  delete fWorldYCmd;
  delete fWorldZCmd;
  delete fDetDir;  
  delete fTestemDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if ( command == fAbsMaterCmd )
   {fDetector->SetAbsorberMaterial(newValue);}
   
  if ( command == fWorldMaterCmd )
   {fDetector->SetWorldMaterial(newValue);}
   
  if ( command == fAbsThickCmd )
  {fDetector->SetAbsorberThickness(fAbsThickCmd->GetNewDoubleValue(newValue));}
   
  if ( command == fAbsSizXYCmd )
   {fDetector->SetAbsorberSizeXY(fAbsSizXYCmd->GetNewDoubleValue(newValue));}
   
  if ( command == fAbsXposCmd )
   {fDetector->SetAbsorberXpos(fAbsXposCmd->GetNewDoubleValue(newValue));}
   
  if ( command == fWorldXCmd )
   {fDetector->SetWorldSizeX(fWorldXCmd->GetNewDoubleValue(newValue));}
   
  if ( command == fWorldYCmd )
   {fDetector->SetWorldSizeY(fWorldYCmd->GetNewDoubleValue(newValue));}

  if ( command == fWorldZCmd )
   {fDetector->SetWorldSizeZ(fWorldZCmd->GetNewDoubleValue(newValue));}
   
}
