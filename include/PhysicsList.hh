#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"

class DetectorConstruction;
class PhysicsListMessenger;

class PhysicsList: public G4VUserPhysicsList
{
  public:
    PhysicsList( DetectorConstruction*);
    virtual ~PhysicsList();

  protected:
    // Construct particle and physics
    virtual void ConstructParticle();
    virtual void ConstructProcess();
 
    void SetCuts();

  protected:
    // these methods construct particles
    void ConstructBosons();
    void ConstructLeptons();
    void ConstructMesons();
    void ConstructBarions();

  protected:

    // these methods construct physics processes and register them

    void ConstructGeneral();
    void ConstructEM();

  public:

    void SetGammaCut(G4double);
    void SetElectronCut(G4double);

    void SetMaxStep(G4double);

  public:

    G4double fMaxChargedStep;

  private:

    G4double fCutForGamma;
    G4double fCutForElectron;

    DetectorConstruction* fDet;
    PhysicsListMessenger* fPhysicsListMessenger;
};

#endif
