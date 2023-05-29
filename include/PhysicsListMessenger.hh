#ifndef PhysicsListMessenger_h
#define PhysicsListMessenger_h 1

#include "G4UImessenger.hh"

class PhysicsList;
class G4UIcmdWithoutParameter;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;

class PhysicsListMessenger: public G4UImessenger
{
  public:
    PhysicsListMessenger(PhysicsList*);
    virtual ~PhysicsListMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    PhysicsList*          fList;

    G4UIcmdWithADoubleAndUnit* fSetMaxStepCmd;

    G4UIcmdWithADoubleAndUnit* fCutGCmd;
    G4UIcmdWithADoubleAndUnit* fCutECmd;
};

#endif
