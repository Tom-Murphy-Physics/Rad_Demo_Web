#include "FieldMessenger.hh"

#include "ElectricFieldSetup.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"



//constructor
FieldMessenger::FieldMessenger(ElectricFieldSetup* fieldSetup)
 : G4UImessenger(),
   fElFieldSetup(fieldSetup),
   fFieldDir(0),
   fStepperCmd(0),
   fElFieldCmd(0),
   fMinStepCmd(0),
   fUpdateCmd(0)
{
  fFieldDir = new G4UIdirectory("/field/");
  fFieldDir->SetGuidance("field tracking control.");

  fStepperCmd = new G4UIcmdWithAnInteger("/field/setStepperType",this);
  fStepperCmd->SetGuidance("Select stepper type for electric field");
  fStepperCmd->SetParameterName("choice",true);
  fStepperCmd->SetDefaultValue(4);
  fStepperCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fUpdateCmd = new G4UIcmdWithoutParameter("/field/update",this);
  fUpdateCmd->SetGuidance("Update calorimeter geometry.");
  fUpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  fUpdateCmd->SetGuidance("if you changed geometrical value(s).");
  fUpdateCmd->AvailableForStates(G4State_Idle);

  fElFieldCmd = new G4UIcmdWithADoubleAndUnit("/field/setFieldZ",this);
  fElFieldCmd->SetGuidance("Define uniform Electric field.");
  fElFieldCmd->SetGuidance("Electric field will be in Z direction.");
  fElFieldCmd->SetGuidance("Value of Electric field has to be given in volt/m");
  fElFieldCmd->SetParameterName("Ez",false,false);
  fElFieldCmd->SetDefaultUnit("volt/m");
  fElFieldCmd->AvailableForStates(G4State_Idle);
 
  fMinStepCmd = new G4UIcmdWithADoubleAndUnit("/field/setMinStep",this);
  fMinStepCmd->SetGuidance("Define minimal step");
  fMinStepCmd->SetParameterName("min step",false,false);
  fMinStepCmd->SetDefaultUnit("mm");
  fMinStepCmd->AvailableForStates(G4State_Idle);
}



//deconstructor
FieldMessenger::~FieldMessenger()
{
  delete fStepperCmd;
  delete fElFieldCmd;
  delete fMinStepCmd;
  delete fFieldDir;
  delete fUpdateCmd;
}



void FieldMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if( command == fStepperCmd )
    fElFieldSetup->SetStepperType(fStepperCmd->GetNewIntValue(newValue));
  if( command == fUpdateCmd )
    fElFieldSetup->UpdateField();
  if( command == fElFieldCmd )
    fElFieldSetup->SetFieldValue(fElFieldCmd->GetNewDoubleValue(newValue));
  if( command == fMinStepCmd )
    fElFieldSetup->SetMinStep(fMinStepCmd->GetNewDoubleValue(newValue));
}
