#ifndef PrimaryGeneratorMessenger_h
#define PrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"

class PrimaryGeneratorAction;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

class PrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    PrimaryGeneratorMessenger(PrimaryGeneratorAction*);
    virtual ~PrimaryGeneratorMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    PrimaryGeneratorAction* fAction;
    G4UIcmdWithAString*        fRndmCmd;
    G4UIcmdWithADoubleAndUnit* fSetXVertexCmd;
    G4UIcmdWithADoubleAndUnit* fSetYVertexCmd;
    G4UIcmdWithADoubleAndUnit* fSetZVertexCmd;
};

#endif
