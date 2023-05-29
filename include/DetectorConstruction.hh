#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4Cache.hh"

class G4Box;
class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;

class G4Material;
class G4UniformMagField;

class DetectorMessenger;
class ElectricFieldSetup;

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction();
    virtual ~DetectorConstruction();

  public:

     void SetAbsorberMaterial (G4String);
     void SetAbsorberThickness(G4double);
     void SetAbsorberRadius(G4double);
     void SetAbsorberInnerRadius(G4double);

     void SetAbsorberZpos(G4double);
  
     void SetPMTMaterial (G4String);
     void SetWinMaterial (G4String);
     void SetSSMaterial(G4String);
  
     void SetWorldMaterial(G4String);
     void SetWorldSizeZ(G4double);
     void SetWorldSizeR(G4double);
  
     virtual G4VPhysicalVolume* Construct();
     virtual void ConstructSDandField();

  public:

     void PrintCalorParameters();

     G4Material* GetWorldMaterial()    {return fWorldMaterial;}
     G4double GetWorldSizeZ()          {return fWorldSizeZ;}
     G4double GetWorldSizeR()          {return fWorldSizeR;}

     G4double GetAbsorberZpos()        {return fZAbsorber;}
     G4double GetZStartAbs()           {return fZStartAbs;}
     G4double GetZEndAbs()             {return fZEndAbs;}

     G4Material* GetAbsorberMaterial() {return fAbsorberMaterial;}
     G4double    GetAbsorberThickness(){return fAbsorberThickness;}
     G4double    GetAbsorberRadius()   {return fAbsorberRadius;}
     G4double    GetAbsorberInnerRadius()   {return fAbsorberInnerRadius;}

     G4Material* GetPMTMaterial() {return fWorldMaterial;}
     G4Material* GetWinMaterial() {return fWinMaterial;}
     G4Material* GetSSMaterial()  {return fSSMaterial;}
  
     const G4VPhysicalVolume* GetPhysiWorld() {return fPhysiWorld;}
     const G4VPhysicalVolume* GetAbsorber()   {return fPhysiAbsorber;}
     const G4VPhysicalVolume* GetPhysiPMT()   {return fPhysiPMT;}
     const G4VPhysicalVolume* GetPhysiWin()   {return fPhysiWin;}
     const G4VPhysicalVolume* GetPhysiSS()    {return fPhysiSS;}
  const G4VPhysicalVolume* GetPhysiTumor()    {return fPhysiTumor;}
  
     G4LogicalVolume* GetLogicalAbsorber()    {return fLogicAbsorber;}

  private:

     DetectorMessenger* fDetectorMessenger;  // pointer -> Messenger
  //G4Cache<CalorimeterSD*> fCalorimeterSD; // pointer -> sensitive detector
     G4Cache<ElectricFieldSetup*> fEmFieldSetup;

     G4Tubs*            fSolidWorld;     // pointer to the solid World
     G4LogicalVolume*   fLogicWorld;     // pointer to the logical World
     G4VPhysicalVolume* fPhysiWorld;     // pointer to the physical World

     G4Tubs*            fSolidAbsorber;  // pointer to the solid Absorber
     G4LogicalVolume*   fLogicAbsorber;  // pointer to the logical Absorber
     G4VPhysicalVolume* fPhysiAbsorber;  // pointer to the physical Absorber
     G4VPhysicalVolume* fPhysiAbsorber2;  // pointer to the physical Absorber

     G4Box*            fSolidPMT;  // pointer to the solid PMT
     G4LogicalVolume*   fLogicPMT;  // pointer to the logical PMT
     G4VPhysicalVolume* fPhysiPMT;  // pointer to the physical PMT

     G4Tubs*            fSolidWin;  // pointer to the solid Window
     G4LogicalVolume*   fLogicWin;  // pointer to the logical Window
     G4VPhysicalVolume* fPhysiWin;  // pointer to the physical Window

     G4Tubs*            fSolidSS;  // pointer to the solid Sample Space
     G4LogicalVolume*   fLogicSS;  // pointer to the logical Sample Space
     G4VPhysicalVolume* fPhysiSS;  // pointer to the physical Sample Space

     G4Tubs* fSolidTumor;
     G4LogicalVolume* fLogicTumor;
     G4VPhysicalVolume* fPhysiTumor;
  
     G4Material*        fAbsorberMaterial;
     G4double           fAbsorberThickness;
     G4double           fAbsorberRadius;
     G4double           fAbsorberInnerRadius;   
     G4bool             fWorldChanged;

     G4double           fZAbsorber;
     G4double           fZStartAbs, fZEndAbs;

     G4Material* fWinMaterial;
     G4Material* fSSMaterial;
  
     G4Material*        fWorldMaterial;
     G4double           fWorldSizeR;
     G4double           fWorldSizeZ;

  private:
 
     void DefineMaterials();
     void ComputeCalorParameters();
     G4VPhysicalVolume* ConstructCalorimeter();
     G4LogicalVolume *fLogicalPMT;
};



inline void DetectorConstruction::ComputeCalorParameters()
{
     // Compute derived parameters of the calorimeter

     fZStartAbs = fZAbsorber-0.5*fAbsorberThickness;
     fZEndAbs   = fZAbsorber+0.5*fAbsorberThickness;
}

#endif
