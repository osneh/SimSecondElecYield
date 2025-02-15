#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

class DetectorMessenger: public G4UImessenger
{
  public:
    DetectorMessenger(DetectorConstruction* );
   ~DetectorMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);
    
  private:
    DetectorConstruction*      fDetector;
    
    G4UIdirectory*             fTestemDir;
    G4UIdirectory*             fDetDir;

    G4UIcmdWithAString*        fAbsMaterCmd;
    G4UIcmdWithADoubleAndUnit* fAbsThickCmd;
    //G4UIcmdWithADoubleAndUnit* fAbsSizYZCmd;
    G4UIcmdWithADoubleAndUnit* fAbsSizXYCmd;

    G4UIcmdWithADoubleAndUnit* fAbsXposCmd;

    G4UIcmdWithAString*        fWorldMaterCmd;
    G4UIcmdWithADoubleAndUnit* fWorldXCmd;
    G4UIcmdWithADoubleAndUnit* fWorldYCmd;
    G4UIcmdWithADoubleAndUnit* fWorldZCmd;

};

#endif

