#include "SteppingVerbose.hh"

#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"



SteppingVerbose::SteppingVerbose()
 : G4SteppingVerbose()
{}



SteppingVerbose::~SteppingVerbose()
{}




void SteppingVerbose::StepInfo(const G4Step *step)
{
  /*
  CopyState();

  G4int prec = G4cout.precision(3);

  if( verboseLevel >= 1 ){
    if( verboseLevel >= 4 ) VerboseTrack();
    if( verboseLevel >= 3 ){
      G4cout << G4endl;
      G4cout << std::setw( 5) << "#Step#"     << " "
             << std::setw( 6) << "X"          << "    "
             << std::setw( 6) << "Y"          << "    "
             << std::setw( 6) << "Z"          << "    "
             << std::setw( 9) << "KineE"      << " "
             << std::setw( 9) << "dEStep"     << " "
             << std::setw(10) << "StepLeng"
             << std::setw(10) << "TrakLeng"
             << std::setw(10) << "NextVolu"
             << std::setw(10) << "Process"   << G4endl;
    }
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  

   
  man->Write();
  man->CloseFile();
    G4cout << std::setw( 5)<<fTrack->GetCurrentStepNumber() << " "
           << std::setw( 6)<<G4BestUnit(fTrack->GetPosition().x(),"Length")
           << std::setw( 6)<<G4BestUnit(fTrack->GetPosition().y(),"Length")
           << std::setw( 6)<<G4BestUnit(fTrack->GetPosition().z(),"Length")
           << std::setw( 6)<<G4BestUnit(fTrack->GetKineticEnergy(),"Energy")
           << std::setw( 6)<<G4BestUnit(fStep->GetTotalEnergyDeposit(),"Energy")
           << std::setw( 6)<<G4BestUnit(fStep->GetStepLength(),"Length")
           << std::setw( 6) << G4BestUnit(fTrack->GetTrackLength(),"Length");
  
    if( fTrack->GetNextVolume() != 0 ) {
      G4cout << std::setw(10) << fTrack->GetNextVolume()->GetName();
    } else {
      G4cout << std::setw(10) << "OutOfWorld";
    }

    if(fStep->GetPostStepPoint()->GetProcessDefinedStep() != 0){
      G4cout << std::setw(10) 
             << fStep->GetPostStepPoint()->GetProcessDefinedStep()
                                         ->GetProcessName();
    } else {
      G4cout << "   UserLimit";
    }

    G4cout << G4endl;

    if( verboseLevel == 2 ){
      G4int tN2ndariesTot = fN2ndariesAtRestDoIt +
                            fN2ndariesAlongStepDoIt +
                            fN2ndariesPostStepDoIt;
      if(tN2ndariesTot>0){
        G4cout << "    :----- List of 2ndaries - "
               << "#SpawnInStep=" << std::setw(3) << tN2ndariesTot
               << "(Rest="  << std::setw(2) << fN2ndariesAtRestDoIt
               << ",Along=" << std::setw(2) << fN2ndariesAlongStepDoIt
               << ",Post="  << std::setw(2) << fN2ndariesPostStepDoIt
               << "), "
               << " ---------------"
               << G4endl;
        G4cout << "    :-----------------------------"
               << "----------------------------------"
               << "-- EndOf2ndaries Info ---------------"
               << G4endl;
      }
    }

  }
  G4cout.precision(prec);
  
*/
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void SteppingVerbose::output(const G4Step *step)
{/*
  G4ThreeVector x = step->GetDeltaPosition();
  
  //G4cout<<"Delta Position: "<< x <<G4endl;
  //G4cout<<event_id<<G4endl;
  
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  
  man->FillNtupleDColumn(0,0, x[0]/x[1]);
  man->FillNtupleDColumn(3, x[2]);

  G4int track_id = step->GetTrack()->GetTrackID();
  man->FillNtupleIColumn(1,track_id);

  G4int event_id = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
  man->FillNtupleIColumn(2,event_id);

  G4double delta_E = step->GetDeltaEnergy();
  man->FillNtupleDColumn(4,delta_E);

  G4String name = step->GetTrack()->GetParticleDefinition()->GetParticleName();
  G4cout<<name<<G4endl;
  G4int type = 0;
  if (name=="gamma"){type = 0;}
  else if (name=="e-"){type = 1;}
  else {type = 2;}
  man->FillNtupleIColumn(5,type);
  
  man->AddNtupleRow(0);*/
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void SteppingVerbose::TrackingStarted()
{/*
  CopyState();
  G4int prec = G4cout.precision(3);
  if( verboseLevel > 0 ){

    G4cout << std::setw( 5) << "Step#"      << " "
           << std::setw( 6) << "X"          << "    "
           << std::setw( 6) << "Y"          << "    "
           << std::setw( 6) << "Z"          << "    "
           << std::setw( 9) << "KineE"      << " "
           << std::setw( 9) << "dEStep"     << " "
           << std::setw(10) << "StepLeng"
           << std::setw(10) << "TrakLeng"
           << std::setw(10) << "NextVolu"
           << std::setw(10) << "Process"    << G4endl;

    G4cout << std::setw( 5)<<fTrack->GetCurrentStepNumber() << " "
           << std::setw( 6)<<G4BestUnit(fTrack->GetPosition().x(),"Length")
           << std::setw( 6)<<G4BestUnit(fTrack->GetPosition().y(),"Length")
           << std::setw( 6)<<G4BestUnit(fTrack->GetPosition().z(),"Length")
           << std::setw( 6)<<G4BestUnit(fTrack->GetKineticEnergy(),"Energy")
           << std::setw( 6)<<G4BestUnit(fStep->GetTotalEnergyDeposit(),"Energy")
           << std::setw( 6)<<G4BestUnit(fStep->GetStepLength(),"Length")
           << std::setw( 6) << G4BestUnit(fTrack->GetTrackLength(),"Length");

    if(fTrack->GetNextVolume()){
      G4cout << std::setw(10) << fTrack->GetNextVolume()->GetName() << " ";
    } else {
      G4cout << std::setw(10) << "OutOfWorld" << " ";
    }
    G4cout << std::setw(10) << "initStep" << G4endl;
  }
  G4cout.precision(prec);*/
}
