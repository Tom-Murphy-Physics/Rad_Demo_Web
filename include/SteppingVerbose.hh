#ifndef SteppingVerbose_h
#define SteppingVerbose_h 1

#include "G4SteppingVerbose.hh"
#include "G4UserSteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"

class SteppingVerbose : public G4SteppingVerbose
{
  public:

    SteppingVerbose();
    virtual ~SteppingVerbose();

    virtual void StepInfo(const G4Step*);
   
    virtual void TrackingStarted();
    virtual void output(const G4Step*);

  private:
    RunAction *fRunAction;

};

#endif
