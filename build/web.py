from flask import Flask, render_template, request, flash
import web_functions as wf
import vis_maker as vm
import subprocess
import time
import os

app = Flask(__name__)

R_levels = [20,20,20,20]
T_levels = [20,15,10,5]
Z_levels = [0,10,20,30]

@app.route('/', methods=['GET', 'POST'])
def home():
	grade = " "
	particle = " "
	energy = " "
	number_of_particles = " "
	beam_angle = 0
	
	with open(".level.txt", "r") as file:
		l = file.read()
	
	level = int(l)
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
			
			#os.system('sed -i "61s/.*//run/beamOn ' + str(number_of_particles) +'/" vis.mac')
			
			if energy_validation[1] == False:
				energy = energy_validation[0]
			if particle_validation[1] == False:
				particle = particle_validation[0]
				grade = "Try again"
			
			if particle_validation[1] == True and energy_validation[1] == True:
				#os.system('sed -i "18s/.*/'+ "/gun/energy " + energy + " MeV"+'/" vis.mac')
				#os.system('sed -i "17s/.*/'+ "/gun/particle " + particle +'/" vis.mac')
				#os.system('sed -i "24s/.*/'+ "/gun/BeamAngle " + str(beam_angle) +' deg/" vis.mac')
				vm.make(particle, energy, beam_angle, number_of_particles, Z_levels[level-1], R_levels[level-1], T_levels[level-1])
				os.system('./Rad_Demo > output.txt &')
				window_number = subprocess.getoutput("wmctrl -lG | grep ' Rad_Demo' | cut -d ' ' -f1")
				while window_number == "":
					window_number = subprocess.getoutput("wmctrl -lG | grep ' Rad_Demo' | cut -d ' ' -f1")
				os.system('wmctrl -ir "' + str(window_number) + '" -e '+'"0,300,162,1600,975"')
				time.sleep(1)
				output = subprocess.run(['root', '-q', '-l', 'grade.C'], capture_output=True, text=True).stdout
				lines = output.split(' ')
				lines = lines[-1].split('\n')
				grade = float(lines[-2])
				#os.system('root -l -q grade.C > .grade.txt')
				#with open('.grade.txt') as f:
				#	for line in f:
				#		pass
				#	grade = float(line)
				#os.system("rm N500_x0.45.root")
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

