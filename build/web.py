from flask import Flask, render_template, request, flash
import web_functions as wf
import subprocess
import time
import os

app = Flask(__name__)

@app.route('/', methods=['GET', 'POST'])
def home():
	grade = " "
	particle = " "
	energy = " "
	number_of_particles = " "
	beam_angle = 0
	if 'level' in locals():
		level = level
	else:
		level = 1
	
	if request.method == 'POST':
			
		if request.form.get('action1') == 'level_reset':
			wf.level_up(100,1)
		elif request.form.get('action2') == 'submit':
			energy = request.form.get("energy")
			particle = request.form.get("particle")
			number_of_particles = request.form.get("number_of_particles")
			beam_angle = request.form.get("beam_angle")
			
			energy_validation = wf.validate_energy(energy)
			particle_validation = wf.validate_particle(particle)
			
			os.system('sed -i "61s/.*/\/run\/beamOn ' + str(number_of_particles) +'/" vis.mac')
			
			if energy_validation[1] == False:
				energy = energy_validation[0]
			if particle_validation[1] == False:
				particle = particle_validation[0]
				grade = "Try again"
			
			if particle_validation[1] == True and energy_validation[1] == True:
				os.system('sed -i "18s/.*/'+ "\/gun\/energy " + energy + " MeV"+'/" vis.mac')
				os.system('sed -i "17s/.*/'+ "\/gun\/particle " + particle +'/" vis.mac')
				os.system('sed -i "24s/.*/'+ "\/gun\/BeamAngle " + str(beam_angle) +' deg/" vis.mac')
				os.system('./Rad_Demo > output.txt &')
				window_number = subprocess.getoutput("wmctrl -lG | grep ' Rad_Demo' | cut -d ' ' -f1")
				while window_number == "":
					window_number = subprocess.getoutput("wmctrl -lG | grep ' Rad_Demo' | cut -d ' ' -f1")
				os.system('wmctrl -ir "' + str(window_number) + '" -e '+'"0,300,162,1600,975"')
				grade = round(os.system('root -l -q grade.C > a.txt')/253.43, 2)
				#os.system("rm N500_x0.45.root")
				print(grade)
				if grade > 100:
					grade = 100
				
				#wf.open_gif(grade)
				
				if grade > 75:
					level += 1
					wf.level_up(grade, level)
				else:
					current_level = level
		
	return render_template('particle.html', grade = grade, energy = energy, particle = particle, level = level, number_of_particles = number_of_particles, beam_angle = beam_angle)
if __name__ == '__main__':
	app.secret_key = 'super secret key'
	app.config['SESSION_TYPE'] = 'filesystem'

	app.debug = True
	app.run()

