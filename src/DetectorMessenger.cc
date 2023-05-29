#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"



//constructor
DetectorMessenger::DetectorMessenger(DetectorConstruction* det)
 : G4UImessenger(),
   fDetector(det),
   fDetDir(0),
   fAbsMaterCmd(0),
   fAbsThickCmd(0),
   fAbsRadCmd(0),
   fAbsZposCmd(0),
   fWorldMaterCmd(0),
   fWorldZCmd(0),
   fWorldRCmd(0)
{
  fDetDir = new G4UIdirectory("/calor/");
  fDetDir->SetGuidance("detector control.");
 
  fAbsMaterCmd = new G4UIcmdWithAString("/calor/setAbsMat",this);
  fAbsMaterCmd->SetGuidance("Select Material of the Absorber.");
  fAbsMaterCmd->SetParameterName("choice",true);
  fAbsMaterCmd->SetDefaultValue("Lead");
  fAbsMaterCmd->AvailableForStates(G4State_Idle);
  fAbsMaterCmd->SetToBeBroadcasted(false);

  fWorldMaterCmd = new G4UIcmdWithAString("/calor/setWorldMat",this);
  fWorldMaterCmd->SetGuidance("Select Material of the World.");
  fWorldMaterCmd->SetParameterName("wchoice",true);
  fWorldMaterCmd->SetDefaultValue("air");
  fWorldMaterCmd->AvailableForStates(G4State_Idle);
  fWorldMaterCmd->SetToBeBroadcasted(false);

  fAbsThickCmd = new G4UIcmdWithADoubleAndUnit("/calor/setAbsThick",this);
  fAbsThickCmd->SetGuidance("Set Thickness of the Absorber");
  fAbsThickCmd->SetParameterName("SizeZ",false,false);
  fAbsThickCmd->SetDefaultUnit("mm");
  fAbsThickCmd->SetRange("SizeZ>0.");
  fAbsThickCmd->AvailableForStates(G4State_Idle);
  fAbsThickCmd->SetToBeBroadcasted(false);

  fAbsRadCmd = new G4UIcmdWithADoubleAndUnit("/calor/setAbsRad",this);
  fAbsRadCmd->SetGuidance("Set radius of the Absorber");
  fAbsRadCmd->SetParameterName("SizeR",false,false);
  fAbsRadCmd->SetDefaultUnit("mm");
  fAbsRadCmd->SetRange("SizeR>0.");
  fAbsRadCmd->AvailableForStates(G4State_Idle);
  fAbsRadCmd->SetToBeBroadcasted(false);

  fAbsZposCmd = new G4UIcmdWithADoubleAndUnit("/calor/setAbsZpos",this);
  fAbsZposCmd->SetGuidance("Set Z pos. of the Absorber");
  fAbsZposCmd->SetParameterName("Zpos",false,false);
  fAbsZposCmd->SetDefaultUnit("mm");
  fAbsZposCmd->AvailableForStates(G4State_Idle);
  fAbsZposCmd->SetToBeBroadcasted(false);

  fWorldZCmd = new G4UIcmdWithADoubleAndUnit("/calor/setWorldZ",this);
  fWorldZCmd->SetGuidance("Set Z size of the World");
  fWorldZCmd->SetParameterName("WSizeZ",false,false);
  fWorldZCmd->SetDefaultUnit("mm");
  fWorldZCmd->SetRange("WSizeZ>0.");
  fWorldZCmd->AvailableForStates(G4State_Idle);
  fWorldZCmd->SetToBeBroadcasted(false);

  fWorldRCmd = new G4UIcmdWithADoubleAndUnit("/calor/setWorldR",this);
  fWorldRCmd->SetGuidance("Set R size of the World");
  fWorldRCmd->SetParameterName("WSizeR",false,false);
  fWorldRCmd->SetDefaultUnit("mm");
  fWorldRCmd->SetRange("WSizeR>0.");
  fWorldRCmd->AvailableForStates(G4State_Idle);
  fWorldRCmd->SetToBeBroadcasted(false);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//deconstructor
DetectorMessenger::~DetectorMessenger()
{
  delete fAbsMaterCmd;
  delete fAbsThickCmd;
  delete fAbsRadCmd;
  delete fAbsZposCmd;
  delete fWorldMaterCmd;
  delete fWorldZCmd;
  delete fWorldRCmd;
  delete fDetDir;
}



//defines commands in G4 gui
void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if( command == fAbsMaterCmd )
   { fDetector->SetAbsorberMaterial(newValue);}

  if( command == fWorldMaterCmd )
   { fDetector->SetWorldMaterial(newValue);}
 
  if( command == fAbsThickCmd )
   {fDetector->SetAbsorberThickness(fAbsThickCmd->GetNewDoubleValue(newValue));}

  if( command == fAbsRadCmd )
   { fDetector->SetAbsorberRadius(fAbsRadCmd->GetNewDoubleValue(newValue));}
 
  if( command == fAbsZposCmd )
   { fDetector->SetAbsorberZpos(fAbsZposCmd->GetNewDoubleValue(newValue));}
 
  if( command == fWorldZCmd )
   { fDetector->SetWorldSizeZ(fWorldZCmd->GetNewDoubleValue(newValue));}
 
  if( command == fWorldRCmd )
   { fDetector->SetWorldSizeR(fWorldRCmd->GetNewDoubleValue(newValue));}
}
