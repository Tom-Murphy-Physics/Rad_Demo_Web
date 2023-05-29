#include "RunAction.hh"
#include "RunMessenger.hh"

#include "G4Run.hh"
#include "G4UImanager.hh"
#include "G4VVisManager.hh"

#include "Randomize.hh"



//constructor
RunAction::RunAction()
  : G4UserRunAction(),
    fMessenger(0),
    fSaveRndm(0)
{
  fMessenger = new RunMessenger(this);

  G4AnalysisManager *man = G4AnalysisManager::Instance();
  
  man->CreateNtuple("Hits","Hits");

  man->CreateNtupleDColumn("mx_y");
  man->CreateNtupleIColumn("track_id");
  man->CreateNtupleIColumn("event_id");
  man->CreateNtupleDColumn("delta_z");
  man->CreateNtupleDColumn("delta_E_good");
  man->CreateNtupleDColumn("delta_E_bad");
  man->CreateNtupleIColumn("type");
  man->CreateNtupleIColumn("fdetected_sp");
  man->FinishNtuple(0);
}



//deconstructor
RunAction::~RunAction()
{
  delete fMessenger;
}




void RunAction::BeginOfRunAction(const G4Run* run)
{
  //Defines names of ROOT files that make some sense 
  G4AnalysisManager *man = G4AnalysisManager::Instance();

  G4float runNumber = run->GetRunID();

  std::stringstream strRunID;
  runNumber = (float(runNumber))*0.05+0.40;
  if (int(runNumber*100)%10==0)
    {
      if (runNumber==1)
	{
	  strRunID <<runNumber;
  
	  man->OpenFile("N500_x"+strRunID.str()+".00.root");
	}
      else
	{
	  strRunID <<runNumber;
  
	  man->OpenFile("N500_x"+strRunID.str()+"0.root");
	}
    }
  else
    {
      strRunID <<runNumber;
  
      man->OpenFile("N500_x"+strRunID.str()+".root");
    }
  
  // save Rndm status
  if (fSaveRndm > 0)
  {
      G4Random::showEngineStatus();
      G4Random::saveEngineStatus("beginOfRun.rndm");
  }
  G4UImanager* ui = G4UImanager::GetUIpointer();
 
  G4VVisManager* visManager = G4VVisManager::GetConcreteInstance();

  if (visManager) ui->ApplyCommand("/vis/scene/notifyHandlers");


}




void RunAction::EndOfRunAction(const G4Run*)
{
  //Fills the ROOT file 
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  
  man->FillNtupleDColumn(0,0, fx);
  man->FillNtupleIColumn(2, event_id);
  man->FillNtupleIColumn(1, track_id);
  man->FillNtupleDColumn(3, delta_z);
  man->FillNtupleDColumn(4,delta_E_good);
  man->FillNtupleDColumn(5,delta_E_bad);
  man->FillNtupleIColumn(6,type);
  man->AddNtupleRow(0);
   
  man->Write();
  man->CloseFile();
  
  if (G4VVisManager::GetConcreteInstance())
  {
    G4UImanager::GetUIpointer()->ApplyCommand("/vis/viewer/update");
  }

  // save Rndm status

  if (fSaveRndm == 1)
  {
    G4Random::showEngineStatus();
    G4Random::saveEngineStatus("endOfRun.rndm");
  }

}
