#include "EventAction.hh"
#include "RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "Randomize.hh"



EventAction::EventAction(RunAction* action)
 : G4UserEventAction(),
   fRunAction(action)
{}



EventAction::~EventAction()
{}



void EventAction::BeginOfEventAction(const G4Event* evt)
{
  G4int evtNb = evt->GetEventID();
  // G4cout << "\n---> End of Event: " << evtNb << G4endl;
}



void EventAction::EndOfEventAction(const G4Event* evt)
{
  
  // save rndm status
  if (fRunAction->GetRndmFreq() == 2)
    {
     G4Random::saveEngineStatus("endOfEvent.rndm");

     G4int evtNb = evt->GetEventID();
     G4int printProgress = G4RunManager::GetRunManager()->GetPrintProgress();
     if (evtNb%printProgress == 0)
       {
	 // G4cout << "\n---> End of Event: " << evtNb << G4endl;
         G4Random::showEngineStatus();
       }
    }
  
}


