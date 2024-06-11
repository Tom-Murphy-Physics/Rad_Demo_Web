import os

particles = ["gamma","e+","e-","mu+","mu-","tau-","tau+","pi0","pi+","pi-","kaon0","kaon+","kaon-","neutron","proton","eta","anti_proton","nu_mu","nu_e"]

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
		
def validate_energy(E):
	try:
		return float(E), True
	except:
		return "Invalid Energy", False
			
gifs = ["no.gif","disappointed.gif", "multifacepalm.gif", "facepalm.gif", "probnot.gif", "meh.gif","decent.gif" , "Thumbsup.gif", ]
				
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
	
R_levels = [20,20,20,20]
T_levels = [20,15,10,5]
Z_levels = [0,10,20,30]
	
def level_up(grade, level):
	if grade > 75:	
		#os.system('sed -i "20s/.*/'+ "\/calor\/setAbsZpos " + str(Z_levels[level-1]) +'/" vis.mac')
		#os.system('sed -i "21s/.*/'+ "\/calor\/setAbsRad " + str(R_levels[level-1]) +'/" vis.mac')
		#os.system('sed -i "22s/.*/'+ "\/calor\/setAbsThick " + str(T_levels[level-1]) +'/" vis.mac')
		with open(".level.txt", "w") as file:
			file.write(str(level))
		return True
	else:	
		return False
