from flask import Flask, render_template, request, send_file
import web_functions as wf
import vis_maker as vm
import subprocess
import time
import os
import glob

app = Flask(__name__)
R_levels = [20,20,20,20]
T_levels = [20,15,10,5]
Z_levels = [0,10,20,30]

SIM_IMAGE = "/app/build/simulation.jpeg"

@app.route('/simulation_image')
def simulation_image():
    if os.path.exists(SIM_IMAGE):
        return send_file(SIM_IMAGE, mimetype='image/jpeg')
    return "No image yet", 404

@app.route('/', methods=['GET', 'POST'])
def home():
    grade = " "
    particle = " "
    energy = " "
    number_of_particles = " "
    beam_angle = 0
    image_ready = False

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

            if energy_validation[1] == False:
                energy = energy_validation[0]
            if particle_validation[1] == False:
                particle = particle_validation[0]
                grade = "Try again"

            if particle_validation[1] == True and energy_validation[1] == True:
                vm.make(particle, energy, beam_angle, number_of_particles,
                        Z_levels[level-1], R_levels[level-1], T_levels[level-1])

                # Run simulation headlessly — no display needed
                subprocess.run(['./Rad_Demo', 'vis.mac'],
                               capture_output=True, timeout=120)

                # RayTracer outputs g4RayTracer.jpeg — rename to stable path
                candidates = glob.glob("g4RayTracer*.jpeg")
                if candidates:
                    os.rename(candidates[0], SIM_IMAGE)
                    image_ready = True

                # Grade as before
                output = subprocess.run(['root', '-q', '-l', 'grade.C'],
                                        capture_output=True, text=True).stdout
                lines = output.split(' ')
                lines = lines[-1].split('\n')
                grade = float(lines[-2])

                if grade > 100:
                    grade = 100

                if grade > 75:
                    level += 1
                    wf.level_up(grade, level)

    return render_template('particle.html', grade=grade, energy=energy,
                           particle=particle, level=level,
                           number_of_particles=number_of_particles,
                           beam_angle=beam_angle, image_ready=image_ready)

if __name__ == '__main__':
    app.secret_key = 'super secret key'
    app.config['SESSION_TYPE'] = 'filesystem'
    app.run(host='0.0.0.0', port=5000, debug=False)
