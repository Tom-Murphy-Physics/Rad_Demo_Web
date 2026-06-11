def make(Particle, Energy, Angle, N_particles, AbsZpos, AbsRad, AbsThick):
    content = """/tracking/verbose 0
/run/verbose 0
/field/setStepperType 4
/field/setMinStep 10 mm
/field/update
/run/initialize
/run/reinitializeGeometry
/run/particle/dumpCutValues
/gun/particle """ + str(Particle) + """
/gun/energy """ + str(Energy) + """ MeV
/calor/setAbsZpos """ + str(AbsZpos) + """
/calor/setAbsRad """ + str(AbsRad) + """
/calor/setAbsThick """ + str(AbsThick) + """
/gun/BeamAngle """ + str(Angle) + """ deg
/process/em/lowestElectronEnergy 10 eV
/vis/open RayTracer
/vis/viewer/set/style wireframe
/vis/drawVolume
/vis/viewer/set/viewpointThetaPhi 90 45.
/vis/viewer/zoom 1
/vis/scene/add/trajectories smooth
/vis/filtering/trajectories/create/particleFilter
/vis/filtering/trajectories/particleFilter-0/add opticalphoton
/vis/filtering/trajectories/particleFilter-0/invert true
/vis/scene/endOfEventAction accumulate
/vis/viewer/set/upVector 0 1 0
/run/beamOn 1
/run/beamOn """ + str(N_particles) + """
/vis/viewer/flush
"""
    with open("vis.mac", "w") as file:
        file.write(content)

if __name__ == "__main__":
    make("e-", 50, 10, 75, 0, 20, 20)
