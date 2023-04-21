#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4UniformMagField.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4UnitsTable.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4VisAttributes.hh"

#include "G4SolidStore.hh"
#include "G4AutoDelete.hh"
#include "G4SDManager.hh"
#include "F02ElectricFieldSetup.hh"
#include "G4SystemOfUnits.hh"


DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fAbsorberMaterial(nullptr),fWorldMaterial(nullptr),
   fSolidWorld(nullptr),fLogicWorld(nullptr),fPhysiWorld(nullptr),
   fSolidAbsorber(nullptr),fLogicAbsorber(nullptr),fPhysiAbsorber(nullptr),
   fDetectorMessenger(nullptr)
{
   
   // default parameter values of the calorimeter
   fAbsorberThickness = 400.*nm;
   fAbsorberSizeXY    = 400.*nm;
   //fXposAbs           = 0.*nm;
   fXposAbs           = 0.;//0.5*fAbsorberThickness;
   ComputeGeomParameters();

   // materials  
   DefineMaterials();

   SetWorldMaterial("G4_Galactic");
   //SetAbsorberMaterial("G4_ALUMINUM_OXIDE");
   SetAbsorberMaterial("G4_Cu");
  // create commands for interactive definition of the calorimeter  
  fDetectorMessenger = new DetectorMessenger(this);
}

DetectorConstruction::~DetectorConstruction()
{
	delete fDetectorMessenger;
}

void DetectorConstruction::DefineMaterials()
{ 
  //This function illustrates the possible ways to define materials
 
  G4String symbol;             //a=mass of a mole;
  G4double a, z, density;      //z=mean number of protons;  

  G4int ncomponents, natoms;
  G4double fractionmass;
  G4double temperature, pressure;
  
  //
  // define Elements
  //
  G4Element* H  = new G4Element("Hydrogen",symbol="H",  z= 1, a=   1.01*g/mole);
  G4Element* C  = new G4Element("Carbon",  symbol="C",  z= 6, a=  12.01*g/mole);
  G4Element* N  = new G4Element("Nitrogen",symbol="N",  z= 7, a=  14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen",  symbol="O",  z= 8, a=  16.00*g/mole);
  G4Element* Na = new G4Element("Sodium",  symbol="Na", z=11, a=  22.99*g/mole);
  G4Element* I  = new G4Element("Iodine",  symbol="I" , z=53, a= 126.90*g/mole);
  G4Element* S  = new G4Element("Sulfur", symbol = "S", z= 16, a = 32.065*g/mole);


  //
  // define simple materials
  //
  new G4Material("H2Liq"    , z= 1, a= 1.01*g/mole, density= 70.8*mg/cm3);
  new G4Material("Beryllium", z= 4, a= 9.01*g/mole, density= 1.848*g/cm3);
  new G4Material("Aluminium", z=13, a=26.98*g/mole, density= 2.700*g/cm3);
  new G4Material("Silicon"  , z=14, a=28.09*g/mole, density= 2.330*g/cm3);

  new G4Material("Iron",     z=26, a= 55.85*g/mole, density= 7.870*g/cm3);
  new G4Material("Copper",   z=29, a= 63.55*g/mole, density= 8.960*g/cm3);
  new G4Material("Germanium",z=32, a= 72.61*g/mole, density= 5.323*g/cm3);
  new G4Material("Silver",   z=47, a=107.87*g/mole, density= 10.50*g/cm3);
  new G4Material("Tungsten", z=74, a=183.85*g/mole, density= 19.30*g/cm3);
  new G4Material("Gold",     z=79, a=196.97*g/mole, density= 19.32*g/cm3);
  new G4Material("Lead",     z=82, a=207.19*g/mole, density= 11.35*g/cm3);


  //
  // define a material from elements.   case 1: chemical molecule
  //

  G4Material* H2O = new G4Material("Water",density= 1.000*g/cm3,ncomponents=2);
  H2O->AddElement(H, natoms=2);
  H2O->AddElement(O, natoms=1);
  H2O->GetIonisation()->SetMeanExcitationEnergy(78*eV);

  G4Material* CH = new G4Material("Plastic",density= 1.04*g/cm3,ncomponents=2);
  CH->AddElement(C, natoms=1);
  CH->AddElement(H, natoms=1);

  G4Material* NaI = new G4Material("NaI", density= 3.67*g/cm3, ncomponents=2);
  NaI->AddElement(Na, natoms=1);
  NaI->AddElement(I , natoms=1);
  NaI->GetIonisation()->SetMeanExcitationEnergy(452*eV);

  G4Material * P3HT = new G4Material("P3HT", density = 1.15*g/cm3, ncomponents=3);
  P3HT->AddElement(H,natoms = 14);
  P3HT->AddElement(O,natoms = 10);
  P3HT->AddElement(S,natoms = 1);

  //
  // define a material from elements.   case 2: mixture by fractional mass
  //

  G4Material* Air = new G4Material("Air", density= 1.290*mg/cm3, ncomponents=2);
  Air->AddElement(N, fractionmass=0.7);
  Air->AddElement(O, fractionmass=0.3);

  G4Material* Air20 = 
    new G4Material("Air20", density= 1.205*mg/cm3, ncomponents=2,
                   kStateGas, 293.*kelvin, 1.*atmosphere);
  Air20->AddElement(N, fractionmass=0.7);
  Air20->AddElement(O, fractionmass=0.3);

  //Graphite
  //
  G4Material* Graphite = 
    new G4Material("Graphite", density= 1.7*g/cm3, ncomponents=1);
  Graphite->AddElement(C, fractionmass=1.);

  //
  // example of vacuum
  //
  density     = universe_mean_density;    //from PhysicalConstants.h
  pressure    = 3.e-18*pascal;
  temperature = 2.73*kelvin;
  new G4Material("Galactic", z=1, a=1.01*g/mole,density,
                 kStateGas,temperature,pressure);
}

void DetectorConstruction::ComputeGeomParameters()
{
  // Compute derived parameters of the calorimeter
  fXstartAbs = fXposAbs-0.5*fAbsorberThickness; 
  fXendAbs   = fXposAbs+0.5*fAbsorberThickness;

  G4double xmax = std::max(std::abs(fXstartAbs), std::abs(fXendAbs));
  fWorldSizeX = 1.2*xmax; 
  //fWorldSizeX = 1.2*xmax; 
  fWorldSizeY= 1.2*fAbsorberSizeXY;
  fWorldSizeZ= 1.2*fAbsorberSizeXY;
  if(nullptr != fPhysiWorld) { ChangeGeometry(); }
}

G4VPhysicalVolume *DetectorConstruction::Construct()
{

  if(nullptr != fPhysiWorld) { return fPhysiWorld; }
  // World
  //
  fSolidWorld = new G4Box("World",                                //its name
                   fWorldSizeX/2,fWorldSizeY/2,fWorldSizeZ/2);  //its size
                         
  fLogicWorld = new G4LogicalVolume(fSolidWorld,          //its solid
                                   fWorldMaterial,        //its material
                                   "World");              //its name
                                   
  fPhysiWorld = new G4PVPlacement(0,                      //no rotation
                                 G4ThreeVector(0.,0.,0.), //at (0,0,0)
                                 fLogicWorld,             //its logical volume
                                 "World",                 //its name
                                 0,                       //its mother  volume
                                 false,                   //no boolean operation
                                 0);                      //copy number
    
  // Absorber
  // 
  //fSolidAbsorber = new G4Box("Absorber",        
  //                    fAbsorberThickness/2,fAbsorberSizeYZ/2,fAbsorberSizeYZ/2);

  fSolidAbsorber = new G4Tubs("Absorber",
                              (fAbsorberSizeXY-350.*nm)/2,(fAbsorberSizeXY-250*nm)/2, fAbsorberThickness/2,
                              0. , 
                              360.*deg);

  fLogicAbsorber = new G4LogicalVolume(fSolidAbsorber,    //its solid
                                       fAbsorberMaterial, //its material
                                       "Absorber");       //its name
                                                
  fPhysiAbsorber = new G4PVPlacement(0,                   //no rotation
                        G4ThreeVector(fXposAbs,0.,0.),    //its position
                                fLogicAbsorber,     //its logical volume
                                "Absorber",         //its name
                                fLogicWorld,        //its mother
                                false,              //no boulean operat
                                0);                 //copy number
                                        
  PrintGeomParameters();    

  // Set visualization attributes
  G4VisAttributes* Target_vis = new G4VisAttributes(G4Colour::Yellow());
  fLogicAbsorber->SetVisAttributes(Target_vis);

  //always return the physical World
  return fPhysiWorld;

}

void DetectorConstruction::PrintGeomParameters()
{
  G4cout << "\n" << fWorldMaterial    << G4endl;
  G4cout << "\n" << fAbsorberMaterial << G4endl;

  G4cout << "\n The  WORLD   is made of "  << G4BestUnit(fWorldSizeX,"Length")
         << " of " << fWorldMaterial->GetName();
  G4cout << ". The transverse size (XZ) of the world is "
         << G4BestUnit(fWorldSizeY,"Length") << G4endl;
  G4cout << " The ABSORBER is made of "
         <<G4BestUnit(fAbsorberThickness,"Length")
         << " of " << fAbsorberMaterial->GetName();
  G4cout << ". The transverse size (XY) is "
         << G4BestUnit(fAbsorberSizeXY,"Length") << G4endl;
  G4cout << " X position of the middle of the absorber "
         << G4BestUnit(fXposAbs,"Length");
  G4cout << G4endl;
}

void DetectorConstruction::SetAbsorberMaterial(const G4String& materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =
    G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);

  if (pttoMaterial && fAbsorberMaterial != pttoMaterial) {
    fAbsorberMaterial = pttoMaterial;                  
    if(fLogicAbsorber) { fLogicAbsorber->SetMaterial(fAbsorberMaterial); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  }
}

void DetectorConstruction::SetWorldMaterial(const G4String& materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =
    G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);

  if (pttoMaterial && fWorldMaterial != pttoMaterial) {
    fWorldMaterial = pttoMaterial; 
    if(fLogicWorld) { fLogicWorld->SetMaterial(fWorldMaterial); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  }
}


void DetectorConstruction::SetAbsorberThickness(G4double val)
{
  fAbsorberThickness = val;
  ComputeGeomParameters();
}

void DetectorConstruction::SetAbsorberSizeXY(G4double val)
{
  fAbsorberSizeXY = val;
  ComputeGeomParameters();
}

void DetectorConstruction::SetWorldSizeX(G4double val)
{
  fWorldSizeX = val;
  ComputeGeomParameters();
}

void DetectorConstruction::SetWorldSizeY(G4double val)
{
  fWorldSizeY = val;
  ComputeGeomParameters();
}

void DetectorConstruction::SetWorldSizeZ(G4double val)
{
  fWorldSizeZ = val;
  ComputeGeomParameters();
}

void DetectorConstruction::SetAbsorberXpos(G4double val)
{
  fXposAbs = val;
  ComputeGeomParameters();
}  

void DetectorConstruction::ConstructSDandField()
{
  //if ( fFieldMessenger.Get() == 0 ) {
  if ( !fEmFieldMessenger.Get()  ) {
  
    // Create global magnetic field messenger.
    // Uniform magnetic field is then created automatically if
    // the field value is not zero.
    //G4ThreeVector fieldValue = G4ThreeVector();
    //G4GlobalMagFieldMessenger* msg =
    //  new G4GlobalMagFieldMessenger(fieldValue);
    //msg->SetVerboseLevel(1);
    //G4AutoDelete::Register(msg);
    //:0fFieldMessenger.Put( msg );      

    F02ElectricFieldSetup* fieldSetup = new F02ElectricFieldSetup();
    G4AutoDelete::Register(fieldSetup); //Kernel will delete the messenger
    fEmFieldSetup.Put(fieldSetup);

  }
}

void DetectorConstruction::ChangeGeometry()
{
  fSolidWorld->SetXHalfLength(fWorldSizeX*0.5);
  fSolidWorld->SetYHalfLength(fWorldSizeY*0.5);
  fSolidWorld->SetZHalfLength(fWorldSizeZ*0.5);

  //fSolidAbsorber->SetXHalfLength(fAbsorberThickness*0.5);
  //fSolidAbsorber->SetYHalfLength(fAbsorberSizeYZ*0.5);
  //fSolidAbsorber->SetZHalfLength(fAbsorberSizeYZ*0.5);


  //fSolidAbsorber->SetXHalfLength(fAbsorberThickness*0.5);
  //fSolidAbsorber->SetYHalfLength(fAbsorberThickness*0.5);
  fSolidAbsorber->SetZHalfLength(fAbsorberThickness*0.5);
}

