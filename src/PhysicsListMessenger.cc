#include "PhysicsListMessenger.hh"

#include "PhysicsList.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"



PhysicsListMessenger::PhysicsListMessenger(PhysicsList * List)
  : fList(List)
{
  fCutGCmd = new G4UIcmdWithADoubleAndUnit("/calor/cutG",this);
  fCutGCmd->SetGuidance("Set cut values by RANGE for Gamma.");
  fCutGCmd->SetParameterName("range",true);
  fCutGCmd->SetDefaultValue(1.);
  fCutGCmd->SetDefaultUnit("mm");
  fCutGCmd->AvailableForStates(G4State_Idle);

  fCutECmd = new G4UIcmdWithADoubleAndUnit("/calor/cutE",this);
  fCutECmd->SetGuidance("Set cut values by RANGE for e- e+.");
  fCutECmd->SetParameterName("range",true);
  fCutECmd->SetDefaultValue(1.);
  fCutECmd->SetDefaultUnit("mm");
  fCutECmd->AvailableForStates(G4State_Idle);

  fSetMaxStepCmd = new G4UIcmdWithADoubleAndUnit("/step/setMaxStep",this);
  fSetMaxStepCmd->SetGuidance("Set max. step length in the detector");
  fSetMaxStepCmd->SetParameterName("mxStep",true);
  fSetMaxStepCmd->SetDefaultUnit("mm");
}



PhysicsListMessenger::~PhysicsListMessenger()
{
  delete fSetMaxStepCmd;
  delete fCutGCmd;
  delete fCutECmd;
}



void PhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{
  if(command == fCutGCmd)
    {fList->SetGammaCut(fCutGCmd->GetNewDoubleValue(newValue));}
  if(command == fCutECmd)
    {fList->SetElectronCut(fCutECmd->GetNewDoubleValue(newValue));}
  if(command == fSetMaxStepCmd)
    {fList->SetMaxStep(fSetMaxStepCmd->GetNewDoubleValue(newValue));}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
