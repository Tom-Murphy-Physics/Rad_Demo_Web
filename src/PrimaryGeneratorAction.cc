#include "PrimaryGeneratorAction.hh"

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorMessenger.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "Randomize.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "G4RandomDirection.hh"

G4ParticleDefinition* PrimaryGeneratorAction::fgPrimaryParticle = 0;



PrimaryGeneratorAction::PrimaryGeneratorAction(
                                            DetectorConstruction* det)
  : G4VUserPrimaryGeneratorAction(),
    fParticleGun(0),
    fDetector(det),
    fGunMessenger(0),
    fRndmFlag("off"),
    fXVertex(0.),
    fYVertex(0.),
    fZVertex(0.),
    fBeamAngle(0.),
    fVertexDefined(false)
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  // create a messenger for this class
  fGunMessenger = new PrimaryGeneratorMessenger(this);

  // default particle kinematic

  //defines gamma ray
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName = "gamma";
  G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
  fParticleGun->SetParticleDefinition(particle);

  fgPrimaryParticle = particle;
  //gives it a random direction of momentum (biased to be in z direction 
  G4double pxi = (G4UniformRand()-0.5)/30;
  G4double pyi = (G4UniformRand()-0.5)/30;
  G4double pzi = G4UniformRand();

  //normalizes it
  G4double normalization = pow(pow(pxi,2)+pow(pyi,2)+pow(pzi,2),0.5);

  //normalizes the momentum vector
  pxi = pxi/normalization;
  pyi = pyi/normalization;
  pzi = pzi/normalization;

  //defines the gamma's kinematics 
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(pxi,pyi,pzi));
  //fParticleGun->SetParticleEnergy(511.*keV);

  G4double phi = 10*deg;
  G4double a = 2*phi*G4UniformRand() + 90*deg - phi;
  G4double theta0 = 0*deg;
  double b = 2*theta0*G4UniformRand() + 90*deg - theta0;
  G4ThreeVector v(std::cos(a)*std::sin(b), std::sin(a)*std::sin(b), std::cos(b));
  v.set(v.y(), v.z(),v.x());
  fParticleGun->SetParticleMomentumDirection(v);
  
  //inital position is redefined 
  fZVertex = -0.225*m;
  fParticleGun->SetParticlePosition(G4ThreeVector(fXVertex,fYVertex,fZVertex));
}



PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fGunMessenger;
}



void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  // this function is called at the begining of event
  //
  fgPrimaryParticle = fParticleGun->GetParticleDefinition();
  // Definition of where the particle will start by default
  G4double x0,y0,z0;
  G4double multiplier = 0.50;
  if (fVertexDefined)
  {
    x0 = fXVertex;
    y0 = fYVertex;
    z0 = fZVertex;
  }
  else
  {
    x0 = 0.;
    y0 = 0.;
    //z0 = -(0.144018+0.015)*multiplier*m;
    //z0 = -0.225*multiplier*m;
    //z0 = -0.075*m-(fDetector->GetWorldSizeZ())/2+1/4*(fDetector->GetAbsorberThickness());
    z0 = -fDetector->GetWorldSizeZ()/2 - fDetector->GetAbsorberThickness() - 0.0375 *m;
  }

  G4double r0,phi0;
  if (fRndmFlag == "on")
  {
    r0 = (fDetector->GetAbsorberRadius())*std::sqrt(G4UniformRand());
    phi0 = twopi*G4UniformRand();
    x0 = r0*std::cos(phi0);
    y0 = r0*std::sin(phi0);
    z0 = -fDetector->GetWorldSizeZ()/2 - fDetector->GetAbsorberThickness() - 0.0375 *m;
  }

  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  fParticleGun->GeneratePrimaryVertex(anEvent);

  //gives it a random direction of momentum (biased to be in z direction 
  G4double pxi = (G4UniformRand()-0.5)/10;
  G4double pyi = (G4UniformRand()-0.5)/10;
  G4double pzi = G4UniformRand();
  while (pzi<0.9)
    {
      pzi = G4UniformRand();
    }
 
  //normalizes it
  G4double normalization = pow(pow(pxi,2)+pow(pyi,2)+pow(pzi,2),0.5);

  //normalizes the momentum vector
  pxi = pxi/normalization;
  pyi = pyi/normalization;
  pzi = pzi/normalization;

  //defines the gamma's kinematics 
  //fParticleGun->SetParticleMomentumDirection(G4ThreeVector(pxi,pyi,pzi));
  G4double theta0 = fBeamAngle;
  G4double theta1 = 2*theta0*G4UniformRand() + 90*deg - theta0;
  G4double tan_theta = 1/tan(theta1);
  G4double phi = 180*deg;
  G4double a = 2*phi*G4UniformRand() + 90*deg - phi;
  G4ThreeVector v(std::cos(a)*tan_theta, std::sin(a)*tan_theta, 1);
  G4double Normalization = pow(pow(v.x(),2) + pow(v.y(),2) + pow(v.z(),2), 0.5);
  
  v.set(v.x()/Normalization, v.y()/Normalization, v.z()/Normalization);
  //G4cout<<v.x()<<" "<<v.y()<<" "<<v.z()<<G4endl;
  fParticleGun->SetParticleMomentumDirection(v);
  //fParticleGun->SetParticleEnergy(511.*keV);
}



G4String PrimaryGeneratorAction::GetPrimaryName()
{
   return fgPrimaryParticle->GetParticleName();
}



void PrimaryGeneratorAction::SetXVertex(G4double x)
{
  fVertexDefined = true;
  fXVertex = x;
  G4cout << " X coordinate of the primary vertex = " << fXVertex/mm <<
            " mm." << G4endl;
}



void PrimaryGeneratorAction::SetYVertex(G4double y)
{
  fVertexDefined = true;
  fYVertex = y;
  G4cout << " Y coordinate of the primary vertex = " << fYVertex/mm <<
            " mm." << G4endl;
}



void PrimaryGeneratorAction::SetZVertex(G4double z)
{
  fVertexDefined = true;
  fZVertex = z;
  G4cout << " Z coordinate of the primary vertex = " << fZVertex/mm <<
            " mm." << G4endl;
}

void PrimaryGeneratorAction::SetBeamAngle(G4double theta)
{
  fBeamAngle = theta;
  G4cout<< "The beam's opening angle is = " << fBeamAngle <<G4endl;
}
