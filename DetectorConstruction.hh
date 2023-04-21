#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"
#include "globals.hh"
#include "G4Cache.hh"

class G4Box;
class G4Tubs;
class G4VPhysicalVolume;
class G4Material;
class G4MaterialCutsCouple;
class G4UniformMagField;
class DetectorMessenger;
class G4GlobalMagFieldMessenger;

class F02ElectricFieldSetup;


class DetectorConstruction : public G4VUserDetectorConstruction
{
public:

  explicit DetectorConstruction();
  virtual ~DetectorConstruction();

  void SetAbsorberMaterial (const G4String&);
  void SetAbsorberThickness(G4double);
  //void SetAbsorberSizeYZ   (G4double);
  void SetAbsorberSizeXY   (G4double);

  void SetAbsorberXpos(G4double);

  void SetWorldMaterial(const G4String&);
  void SetWorldSizeX   (G4double);
  //void SetWorldSizeYZ  (G4double);
  void SetWorldSizeY  (G4double);
  void SetWorldSizeZ  (G4double);

  void SetMagField(G4double);

  G4VPhysicalVolume* Construct() override;
  void ConstructSDandField() override;

  void PrintGeomParameters();

  const G4Material* GetAbsorberMaterial() const {return fAbsorberMaterial;};
  G4double GetAbsorberThickness() const         {return fAbsorberThickness;};
  //G4double GetAbsorberSizeYZ() const            {return fAbsorberSizeYZ;};
  G4double GetAbsorberSizeXY() const            {return fAbsorberSizeXY;};

  G4double GetAbsorberXpos() const              {return fXposAbs;};
  G4double GetxstartAbs() const                 {return fXstartAbs;};
  G4double GetxendAbs() const                   {return fXendAbs;};

  const G4Material* GetWorldMaterial() const    {return fWorldMaterial;};
  G4double GetWorldSizeX() const                {return fWorldSizeX;};
  G4double GetWorldSizeZ() const                {return fWorldSizeZ;};

  const G4VPhysicalVolume* GetAbsorber() const  {return fPhysiAbsorber;};

private:

  void DefineMaterials();
  void ComputeGeomParameters();
  void ChangeGeometry();

  G4Cache<F02ElectricFieldSetup*> fEmFieldSetup;

  G4Material*        fAbsorberMaterial;
  G4double           fAbsorberThickness;
  G4double           fAbsorberSizeXY;

  G4double           fXposAbs;
  G4double           fXstartAbs, fXendAbs;

  G4Material*        fWorldMaterial;
  G4double           fWorldSizeX;
  G4double           fWorldSizeY;
  G4double           fWorldSizeZ;

  G4Box*             fSolidWorld;
  G4LogicalVolume*   fLogicWorld;
  G4VPhysicalVolume* fPhysiWorld;

  //G4Box*             fSolidAbsorber;
  G4Tubs*             fSolidAbsorber;
  G4LogicalVolume*   fLogicAbsorber;
  G4VPhysicalVolume* fPhysiAbsorber;
     
  DetectorMessenger* fDetectorMessenger;
  G4Cache<G4GlobalMagFieldMessenger*> fEmFieldMessenger;
};

#endif
