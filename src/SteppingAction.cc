#include <cmath>
#include "SteppingAction.hh"



SteppingAction::SteppingAction()
{
  // fRunAction = runAction;
}



SteppingAction::~SteppingAction()
{}



void SteppingAction::UserSteppingAction(const G4Step *step)
{
  //Infomration that is added to the ROOT file

  //track length 
  G4ThreeVector x = step->GetDeltaPosition();
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->FillNtupleDColumn(0,0, sqrt(x[0]*x[0]+x[1]*x[1]));

  //track ID
  G4int track_id = step->GetTrack()->GetTrackID();
  man->FillNtupleIColumn(1,track_id);
  
  //Event ID
  G4int event_id = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  man->FillNtupleIColumn(2,event_id);

  //Delta Z distance  
  man->FillNtupleDColumn(3, x[2]);

  //Change in energy
  //G4String geometry = step->GetTrack()->GetVolume()->GetLogicalVolume();
  G4String volume = step->GetTrack()->GetVolume()->GetLogicalVolume()->GetName();

  G4double delta_E = step->GetTotalEnergyDeposit();
  if (volume == "Tumor")
    {
      man->FillNtupleDColumn(4,delta_E);
    }
  else
    {
      man->FillNtupleDColumn(5,delta_E);
    }

  //Type of particle
  G4int charge = step->GetTrack()->GetParticleDefinition()->GetPDGCharge();
  man->FillNtupleIColumn(6,charge);
  man->AddNtupleRow(0);
}
void SteppingAction::stop(const G4Step *step)
{
  G4Track* track = step->GetTrack();
  G4ParticleDefinition* particleType = track->GetDefinition();

  //if(particleType == G4OpticalPhoton::OpticalPhotonDefinition()) track ->SetTrackStatus(fStopAndKill);
}
