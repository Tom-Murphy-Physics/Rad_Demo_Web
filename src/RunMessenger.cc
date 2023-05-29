#include "RunMessenger.hh"

#include "RunAction.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "Randomize.hh"



//constructor
RunMessenger::RunMessenger(RunAction* action)
 : G4UImessenger(),
   fRunAction(action),
   fRndmDir(0),
   fRndmSaveCmd(0),
   fRndmReadCmd(0)
{
  fRndmDir = new G4UIdirectory("/rndm/");
  fRndmDir->SetGuidance("Rndm status control.");

  fRndmSaveCmd = new G4UIcmdWithAnInteger("/rndm/save",this);
  fRndmSaveCmd->
          SetGuidance("set frequency to save rndm status on external files.");
  fRndmSaveCmd->SetGuidance("freq = 0 not saved");
  fRndmSaveCmd->SetGuidance("freq > 0 saved on: beginOfRun.rndm");
  fRndmSaveCmd->SetGuidance("freq = 1 saved on:   endOfRun.rndm");
  fRndmSaveCmd->SetGuidance("freq = 2 saved on: endOfEvent.rndm");
  fRndmSaveCmd->SetParameterName("frequency",false);
  fRndmSaveCmd->SetRange("frequency>=0 && frequency<=2");
  fRndmSaveCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fRndmReadCmd = new G4UIcmdWithAString("/rndm/read",this);
  fRndmReadCmd->SetGuidance("get rndm status from an external file.");
  fRndmReadCmd->SetParameterName("fileName",true);
  fRndmReadCmd->SetDefaultValue ("beginOfRun.rndm");
  fRndmReadCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
}



//deconstructor
RunMessenger::~RunMessenger()
{
  delete fRndmSaveCmd;
  delete fRndmReadCmd;
  delete fRndmDir;
}



void RunMessenger::SetNewValue(G4UIcommand* command,G4String newValues)
{
  if (command == fRndmSaveCmd)
      fRunAction->SetRndmFreq(fRndmSaveCmd->GetNewIntValue(newValues));

  if (command == fRndmReadCmd)
    {G4cout << "\n---> rndm status restored from file: " << newValues << G4endl;
     G4Random::restoreEngineStatus(newValues);
     G4Random::showEngineStatus();
    }
}
