#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "globals.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;
class G4Event;
class DetectorConstruction;
class PrimaryGeneratorMessenger;
class G4ParticleDefinition;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction(DetectorConstruction*);
    virtual ~PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);
    void SetRndmFlag(G4String val) { fRndmFlag = val; }
    void SetXVertex(G4double x);
    void SetYVertex(G4double y);
    void SetZVertex(G4double z);

    static G4String GetPrimaryName();

  private:
    G4ParticleGun*                fParticleGun; //pointer a to G4 service class
    DetectorConstruction*      fDetector;    //pointer to the geometry

    PrimaryGeneratorMessenger* fGunMessenger; //messenger of this class
    G4String                      fRndmFlag;     //flag for random impact point

    static G4ParticleDefinition* fgPrimaryParticle;
    G4double fXVertex, fYVertex, fZVertex;
    G4bool fVertexDefined;

};

#endif
