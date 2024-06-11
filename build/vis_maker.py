def make(Particle, Energy, Angle, N_particles, AbsZpos, AbsRad, AbsThick):
	content = """
	/tracking/verbose 0

	/run/verbose 0

	/field/setStepperType 4
	/field/setMinStep 10 mm

	/field/update

	/run/initialize

	/run/reinitializeGeometry

	/run/particle/dumpCutValues

	/gun/particle """
	content += str(Particle)
	content+= """
	/gun/energy """
	content += str(Energy)
	content += """ MeV

	/calor/setAbsZpos """
	content += str(AbsZpos) 
	content += """
	/calor/setAbsRad """
	content += str(AbsRad)
	content+= """
	/calor/setAbsThick """
	content += str(AbsThick)
	content += """

	/gun/BeamAngle """
	content += str(Angle)
	content += """ deg
	"""
	content += """
	/process/em/lowestElectronEnergy 10 eV
	# Use this open statement to create an OpenGL view:
	/vis/open OGL 600x600-0+0

	/vis/scene/add/trajectories smooth

	# Disable auto refresh and quieten vis messages whilst scene and
	# trajectories are established:
	/vis/viewer/set/autoRefresh True
	/vis/verbose errors

	# Draw geometry:
	/vis/viewer/set/style wireframe
	/vis/drawVolume

	# Specify view angle:
	/vis/viewer/set/viewpointThetaPhi 90 45.

	# Specify zoom value:
	/vis/viewer/zoom 1

	# Draw smooth trajectories at end of event, showing trajectory points
	# as markers 2 pixels wide:
	/vis/scene/add/trajectories smooth

	/vis/filtering/trajectories/create/particleFilter
	/vis/filtering/trajectories/particleFilter-0/add opticalphoton
	/vis/filtering/trajectories/particleFilter-0/invert true

	/vis/scene/endOfEventAction accumulate

	/vis/touchable/set/visibility True

	/run/beamOn 1

	/run/beamOn """
	content += str(N_particles)

	# Create and write to vis.mac
	with open("vis.mac", "w") as file:
	    file.write(content)

if __name__ == "__main__":
	make("e-", 50, 10, 75, 0, 20, 20)
