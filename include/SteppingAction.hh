#ifndef STEPPING_HH
#define STEPPING_HH

#include "G4UserSteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#include "G4OpticalPhoton.hh"

class SteppingAction : public G4UserSteppingAction
{
public:
  // SteppingAction(RunAction* runAction);
  SteppingAction();
  ~SteppingAction();

  virtual void UserSteppingAction(const G4Step*);
  virtual void stop(const G4Step*);

private:
  RunAction *fRunAction;
};

#endif
