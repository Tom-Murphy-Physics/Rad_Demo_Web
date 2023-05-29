#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingVerbose.hh"

#include "DetectorConstruction.hh"



//constructor
ActionInitialization::ActionInitialization
                            (DetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}



//deconstructor
ActionInitialization::~ActionInitialization()
{}



//runs run action
void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction());
}



//does the detector construction, run action, and event action stuff
void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction(fDetConstruction));

  RunAction* runAction = new RunAction();
  SetUserAction(runAction);
  EventAction* eventAction = new EventAction(runAction);
  SetUserAction(eventAction);
}



G4VSteppingVerbose* ActionInitialization::InitializeSteppingVerbose() const
{
  return new SteppingVerbose();
}
