#include "Detector.hh"



//constructor 
MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}



//deconstructor
MySensitiveDetector::~MySensitiveDetector()
{}



//When particle passes through the region of the sensitive detector do this
G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
  //gets track that the step is associated with 
  G4Track *track = aStep->GetTrack();

  //if on will stop tracks when they hit this medium
  track->SetTrackStatus(fStopAndKill);

  //gets point before and after it hits the detector
  G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
  G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

  //gets position of the photon 
  G4ThreeVector posPhoton = preStepPoint->GetPosition();
  //G4cout<<"Photon position: "<<posPhoton<<G4endl;

  //Gets the number of the detector that it hit (not relevant here)
  const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();
  G4int copyNo = touchable->GetCopyNumber();

  //G4cout<<"hit"<<G4endl;

  //Fills the root file. The important thing here is man->...(5,3) this is where we store the "type"
  //3 means it is a detected particle assume all detected are optical photons
  G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->FillNtupleDColumn(0,0);
  man->FillNtupleIColumn(1,0);
  man->FillNtupleIColumn(2,evt);
  man->FillNtupleDColumn(3,evt);
  man->FillNtupleDColumn(4,evt);
  man->FillNtupleIColumn(5,3);
  man->FillNtupleIColumn(6,evt);
  man->AddNtupleRow(0);
}


//constructor 
MySensitiveDetectorA::MySensitiveDetectorA(G4String name) : G4VSensitiveDetector(name)
{}



//deconstructor
MySensitiveDetectorA::~MySensitiveDetectorA()
{}



//When particle passes through the region of the sensitive detector do this
G4bool MySensitiveDetectorA::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
  //gets track that the step is associated with 
  G4Track *track = aStep->GetTrack();

  //if on will stop tracks when they hit this medium
  track->SetTrackStatus(fStopAndKill);
}
