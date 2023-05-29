#ifndef StepCut_h
#define StepCut_h 1

#include "G4VDiscreteProcess.hh"

class StepCut : public G4VDiscreteProcess
{
  public:

     StepCut(const G4String& processName ="UserStepCut" );
     StepCut(StepCut &);

     virtual ~StepCut();

     virtual G4double PostStepGetPhysicalInteractionLength(
                             const G4Track& track,
                             G4double   previousStepSize,
                             G4ForceCondition* condition
                            );

     virtual G4VParticleChange* PostStepDoIt(
                             const G4Track&,
                             const G4Step& 
                            );

    void SetMaxStep(G4double);

  protected:

     // it is not needed here !
     virtual G4double GetMeanFreePath(const G4Track& aTrack,
                             G4double   previousStepSize,
                             G4ForceCondition* condition
                            );

  private:

     // hide assignment operator as private
     StepCut & operator=(const StepCut &right);

  private:

     G4double fMaxChargedStep;
};



// inlined function members implementation
inline G4double StepCut::PostStepGetPhysicalInteractionLength(
                             const G4Track& aTrack,
                             G4double,
                             G4ForceCondition* condition)
{
  // condition is set to "Not Forced"
  *condition = NotForced;

   G4double proposedStep = DBL_MAX;

   if((fMaxChargedStep > 0.) &&
      (aTrack.GetVolume() != 0) &&
      (aTrack.GetVolume()->GetName() == "Absorber") &&
      (aTrack.GetDynamicParticle()->GetDefinition()->GetPDGCharge() != 0.))
        proposedStep = fMaxChargedStep;

   return proposedStep;
}




inline G4VParticleChange* StepCut::PostStepDoIt(
                             const G4Track& aTrack,
                             const G4Step&
                            )
{
   // do nothing
   aParticleChange.Initialize(aTrack);
   return &aParticleChange;
}



inline G4double StepCut::GetMeanFreePath(const G4Track&,
                             G4double,
                             G4ForceCondition*)
{
  return 0.;
}

#endif
