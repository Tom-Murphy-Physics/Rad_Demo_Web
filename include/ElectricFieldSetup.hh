#ifndef ElectricFieldSetup_h
#define ElectricFieldSetup_h 1

#include "G4ElectricField.hh"
#include "G4UniformElectricField.hh"

class G4FieldManager;
class G4ChordFinder;
class G4EquationOfMotion;
class G4Mag_EqRhs;
class G4EqMagElectricField;
class G4MagIntegratorStepper;
class G4MagInt_Driver;
class FieldMessenger;

/// A class for control of the Electric Field of the detector.
///
/// The field for this case is uniform.
/// It is simply a 'setup' class that creates the field and necessary
/// other parts

class ElectricFieldSetup
{
public:
  ElectricFieldSetup(G4ThreeVector);  //  The value of the field
  ElectricFieldSetup();               //  A zero field

  virtual ~ElectricFieldSetup();

  void SetStepperType( G4int i) { fStepperType = i ; }

  void SetStepper();

  void SetMinStep(G4double s) { fMinStep = s ; }

  void UpdateField();

  void SetFieldValue(G4ThreeVector fieldVector);
  void SetFieldValue(G4double      fieldValue);
  G4ThreeVector GetConstantFieldValue();

protected:

  // Find the global Field Manager

  G4FieldManager*         GetGlobalFieldManager();

private:

  G4FieldManager*         fFieldManager;

  G4ChordFinder*          fChordFinder;

  G4EqMagElectricField*   fEquation;

  G4ElectricField*        fEMfield;
 
  G4ThreeVector           fElFieldValue;

  G4MagIntegratorStepper* fStepper;
  G4MagInt_Driver*        fIntgrDriver;

  G4int                   fStepperType;

  G4double                fMinStep;
 
  FieldMessenger*      fFieldMessenger;

};

#endif
