#include "StepCut.hh"

#include "G4Step.hh"
#include "G4UserLimits.hh"
#include "G4VParticleChange.hh"
#include "G4EnergyLossTables.hh"



StepCut::StepCut(const G4String& aName)
 : G4VDiscreteProcess(aName),
   fMaxChargedStep(DBL_MAX)
{
   if (verboseLevel>0) {
     //G4cout << GetProcessName() << " is created "<< G4endl;
   }
}



StepCut::~StepCut()
{}



StepCut::StepCut(StepCut& right)
 : G4VDiscreteProcess(right)
{}



void StepCut::SetMaxStep(G4double step)
{
  fMaxChargedStep = step;
}
