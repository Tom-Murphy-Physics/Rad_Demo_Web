#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "G4UImessenger.hh"

class DetectorConstruction;

class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

class DetectorMessenger: public G4UImessenger
{
  public:
    DetectorMessenger(DetectorConstruction* );
    virtual ~DetectorMessenger();

    virtual void SetNewValue(G4UIcommand*, G4String);

  private:

    DetectorConstruction*   fDetector;

    G4UIdirectory*             fDetDir;

    G4UIcmdWithAString*        fAbsMaterCmd;
    G4UIcmdWithADoubleAndUnit* fAbsThickCmd;
    G4UIcmdWithADoubleAndUnit* fAbsRadCmd;

    G4UIcmdWithADoubleAndUnit* fAbsZposCmd;

    G4UIcmdWithAString*        fWorldMaterCmd;
    G4UIcmdWithADoubleAndUnit* fWorldZCmd;
    G4UIcmdWithADoubleAndUnit* fWorldRCmd;

    G4UIcmdWithADoubleAndUnit* frxCmd;

    
};

#endif
