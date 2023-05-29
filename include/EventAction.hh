#ifndef EventAction_h
#define EventAction_h 1

#include "globals.hh"
#include "G4UserEventAction.hh"

class RunAction;

class EventAction : public G4UserEventAction
{
  public:
    EventAction(RunAction* RA);
    virtual ~EventAction();

  public:
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
  //void Addx(G4double x) {fx = x;}
  private:
    RunAction* fRunAction;
};

#endif
