#ifndef FieldMessenger_h
#define FieldMessenger_h 1

#include "G4UImessenger.hh"

class ElectricFieldSetup;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

class FieldMessenger: public G4UImessenger
{
  public:
    FieldMessenger(ElectricFieldSetup* );
    virtual ~FieldMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:

    ElectricFieldSetup*     fElFieldSetup;

    G4UIdirectory*             fFieldDir;
    G4UIcmdWithAnInteger*      fStepperCmd;
    G4UIcmdWithADoubleAndUnit* fElFieldCmd;
    G4UIcmdWithADoubleAndUnit* fMinStepCmd;
    G4UIcmdWithoutParameter*   fUpdateCmd;
};

#endif
