#include "PrimaryGeneratorMessenger.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4SystemOfUnits.hh"



PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(
                                           PrimaryGeneratorAction* action)
 : G4UImessenger(),
   fAction(action),
   fRndmCmd(0),
   fSetXVertexCmd(0),
   fSetYVertexCmd(0),
   fSetZVertexCmd(0)
{
  fRndmCmd = new G4UIcmdWithAString("/gun/random",this);
  fRndmCmd->SetGuidance("Shoot randomly the incident particle.");
  fRndmCmd->SetGuidance("  Choice : on, off(default)");
  fRndmCmd->SetParameterName("choice",true);
  fRndmCmd->SetDefaultValue("off");
  fRndmCmd->SetCandidates("on off");
  fRndmCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 
  fSetXVertexCmd = new G4UIcmdWithADoubleAndUnit("/gun/xvertex",this);
  fSetXVertexCmd->SetGuidance(" Set x coord. of the primary vertex.");
  fSetXVertexCmd->SetParameterName("xv",true);
  fSetXVertexCmd->SetDefaultValue(0.0*mm);
  fSetXVertexCmd->SetDefaultUnit("mm");

  fSetYVertexCmd = new G4UIcmdWithADoubleAndUnit("/gun/yvertex",this);
  fSetYVertexCmd->SetGuidance(" Set y coord. of the primary vertex.");
  fSetYVertexCmd->SetParameterName("yv",true);
  fSetYVertexCmd->SetDefaultValue(0.0*mm);
  fSetYVertexCmd->SetDefaultUnit("mm");

  fSetZVertexCmd = new G4UIcmdWithADoubleAndUnit("/gun/zvertex",this);
  fSetZVertexCmd->SetGuidance(" Set z coord. of the primary vertex.");
  fSetZVertexCmd->SetParameterName("zv",true);
  fSetZVertexCmd->SetDefaultValue(0.0*mm);
  fSetZVertexCmd->SetDefaultUnit("mm");

}



PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete fRndmCmd;
  delete fSetXVertexCmd;
  delete fSetYVertexCmd;
  delete fSetZVertexCmd;
}



void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand * command,
                                               G4String newValue)
{
  if( command == fRndmCmd )
   { fAction->SetRndmFlag(newValue);}
  if( command == fSetXVertexCmd )
   { fAction->SetXVertex(fSetXVertexCmd->GetNewDoubleValue(newValue));}
  if( command == fSetYVertexCmd )
   { fAction->SetYVertex(fSetYVertexCmd->GetNewDoubleValue(newValue));}
  if( command == fSetZVertexCmd )
   { fAction->SetZVertex(fSetZVertexCmd->GetNewDoubleValue(newValue));}
}

