#ifndef RunMessenger_h
#define RunMessenger_h 1

#include "G4UImessenger.hh"

class RunAction;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;

class RunMessenger: public G4UImessenger
{
  public:

   RunMessenger(RunAction* );
   virtual ~RunMessenger();

   virtual void SetNewValue(G4UIcommand* ,G4String );

  private:

   RunAction*              fRunAction;

   G4UIdirectory*             fRndmDir;

   G4UIcmdWithAnInteger*      fRndmSaveCmd;
   G4UIcmdWithAString*        fRndmReadCmd;
 
};

#endif
