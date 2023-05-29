import PySimpleGUI as sg
import subprocess
import os
import time

def gui(level):
	particles = ["gamma","e+","e-","mu+","mu-","tau-","tau+","pi0","pi+","pi-","kaon0","kaon+","kaon-","neutron","proton","eta","anti_proton","nu_mu","nu_e"]

	gifs = ["no.gif","disappointed.gif", "multifacepalm.gif", "facepalm.gif", "probnot.gif", "meh.gif","decent.gif" , "Thumbsup.gif", ]
	vis = '~/software/geant4/geant4.10.02.p03/Rad_Demo/build/vis.mac'
	Simulate = '~/software/geant4/geant4.10.02.p03/Rad_Demo/build/Simulate.sh'

	layout = [[sg.Text("",key = "space3",size=(9,5),pad=((1336,0),(0,0)),background_color="white"),
					sg.Text("Particle Type: ",pad=((59,0),(40,0)),background_color="#004c97"),
					sg.In(size=(33, 2),pad=((3,0),(40,0)), enable_events=True, key="particle")],
				
				[sg.Text("",key = "space4",size=(9,3),pad=((1336,0),(0,0)),background_color="white"),
					sg.Text("Energy (MeV): ",pad=((59,0),(0,0)),background_color="#004c97"),
					sg.In(size=(33, 2),pad=((0,0),(0,0)), enable_events=True, key="energy")],
					
				[sg.Text("",key = "space4",size=(9,3),pad=((1336,0),(0,0)),background_color="white"),
					sg.Button("OK",bind_return_key=True,pad=((200,0),(0,0)),key="OK",button_color=("#004c97","white")),
					sg.Text("",key = "grade",background_color="#004c97")],
					
				[sg.Image('logo.png',size=(400,400),pad=((463,463),(0,125))) ,
					sg.Text("",key = "space2",size=(9,62),pad=((10,0),(0,0)),background_color="white")],
				
				[sg.Text("",key = "space",size=(400,4),pad=((0,0),(0,10)),background_color="white")]]
			
	def validate_particle(s):
		if s == "proton" or s == "Proton" or s == "P+" or s == "p+":
			s = "proton"
		elif s == "photon" or s == "Gamma" or s == "gamma" or s == "Photon":
			s = "gamma"
		elif s in particles:
			s = s
		else:
			return "Invalid particle", False
		return s, True

	def close_gif():
		os.system('ps | grep eog > process.txt')
		with open('process.txt') as f:
			processID = f.read()[1:7]
		os.system('kill '+processID)

	def open_gif(grade):
		if grade < 0.1:
			os.system('xdg-open ./gifs/'+gifs[0])
			os.system('wmctrl -r '+gifs[0]+' -e 0,250,463,0,0')
			time.sleep(1.8)
		if grade > 0.1 and grade < 5:
			os.system('xdg-open ./gifs/'+gifs[1])
			os.system('wmctrl -r '+gifs[1]+' -e 0,250,463,0,0')
			time.sleep(1.9)
		if grade > 5 and grade < 10:
			os.system('xdg-open ./gifs/'+gifs[2])
			os.system('wmctrl -r '+gifs[2]+' -e 0,250,463,0,0')
			time.sleep(2)
		if grade > 10 and grade < 15:
			os.system('xdg-open ./gifs/'+gifs[3])
			os.system('wmctrl -r '+gifs[3]+' -e 0,250,463,0,0')
			time.sleep(2.1)
		if grade > 15 and grade < 30:
			os.system('xdg-open ./gifs/'+gifs[4])
			os.system('wmctrl -r '+gifs[4]+' -e 0,250,463,0,0')
			time.sleep(1.3)
		if grade > 30 and grade < 40:
			os.system('xdg-open ./gifs/'+gifs[5])
			os.system('wmctrl -r '+gifs[5]+' -e 0,250,463,0,0')
			time.sleep(1.6)
		if grade > 40 and grade < 60:
			os.system('xdg-open ./gifs/'+gifs[6])
			os.system('wmctrl -r '+gifs[6]+' -e 0,250,463,0,0')
			time.sleep(2)
		if grade > 60:
			os.system('xdg-open ./gifs/'+gifs[7])
			os.system('wmctrl -r '+gifs[7]+' -e 0,250,463,0,0')
			time.sleep(2)
		#print('wmctrl -r '+gifs[7]+' -e 0,250,463,0,0')
		close_gif()
				
	# Create the window
	window = sg.Window("Rad Demo: Level "+str(level), layout, location = (70,0), size = (1850,1199),background_color="#004c97")

	while True:
		event, values = window.read()

		if event == sg.WIN_CLOSED:
			grade = -1
			break
		if event == "particle" or event == "energy":
			window["grade"].update("")
			window['OK'].update(disabled=False)
		if event == "OK":
			window["OK"].update(disabled=True)
			window
			particle = values["particle"] 
			if validate_particle(particle)[1] == True:
											
				new="'s/particle proton/particle "+particle+"/g'"
				old="'s/particle "+particle+"/particle proton/g'"
				
				energy = values["energy"] 
				
				if energy == "" or energy.isnumeric() == False:
					print("Not a valid energy")
					continue
					
				new2="'s/energy 10 MeV/energy "+energy+" MeV/g'"                               
				old2="'s/energy "+energy+" MeV/energy 10 MeV/g'" 
				
				os.system('sed -i '+ new + ' ' + vis)
				os.system('sed -i '+ new2 + ' ' + vis)
							
				os.system('./Rad_Demo > output.txt')
				
				os.system('sed -i '+ old + ' ' + vis)		
				os.system('sed -i '+ old2 + ' ' + vis)
				
				grade = os.system('root -l -q grade.C > a.txt')/250.7
				
				if grade > 100:
					grade = 100
				layout += [sg.Text("Grade = "+str(grade)+"%")]
				
				print("Particle Type: ", particle)
				print("Energy (MeV): ", energy)
				print("Your grade is: ", grade)
				open_gif(grade)
				if grade > 75:
					break
			else:
				print(validate_particle(particle)[0])
	window.close()
	return grade
