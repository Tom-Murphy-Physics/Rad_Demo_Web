import gui
import os

def level_up(grade):
	if grade > 75:
		oldz="'s/setAbsZpos "+str(Z_levels[level-1])+"/setAbsZpos 0/g'"
		oldr="'s/setAbsRad "+str(R_levels[level-1])+"/setAbsRad 20/g'"
		oldt="'s/setAbsThick "+str(T_levels[level-1])+"/setAbsThick 20/g'"
		
		os.system('sed -i '+ oldz + ' ' + vis)		
		os.system('sed -i '+ oldr + ' ' + vis)
		os.system('sed -i '+ oldt + ' ' + vis)
		return True
	else:	
		return False
		
def exit(level):
	oldz="'s/setAbsZpos "+str(Z_levels[level])+"/setAbsZpos 0/g'"
	oldr="'s/setAbsRad "+str(R_levels[level])+"/setAbsRad 20/g'"
	oldt="'s/setAbsThick "+str(T_levels[level])+"/setAbsThick 20/g'"
	
	os.system('sed -i '+ oldz + ' ' + vis)		
	os.system('sed -i '+ oldr + ' ' + vis)
	os.system('sed -i '+ oldt + ' ' + vis)
	
	os.system("wmctrl -r :ACTIVE: -b remove,above")
	
vis = '~/software/geant4/geant4-v10.2.3/Rad_Demo/build/vis.mac'

os.system(". ~/software/geant4/geant4-v10.2.3/Rad_Demo/build/align.sh")

R_levels = [20,20,20,20]
T_levels = [20,15,10,5]
Z_levels = [0,10,20,30]

level = 1
keep_playing = True
while keep_playing == True:
	print("Level ",level)
	grade = gui.gui(level)
	if grade == -1:
		keep_playing == False
		exit(level-2)
		break
	if level_up(grade) == True:
		level += 1
		
		newz="'s/setAbsZpos 0/setAbsZpos "+str(Z_levels[level-1])+"/g'"
		newr="'s/setAbsRad 20/setAbsRad "+str(R_levels[level-1])+"/g'"                               
		newt="'s/setAbsThick 20/setAbsThick "+str(T_levels[level-1])+"/g'" 
		
		os.system('sed -i '+ newz + ' ' + vis)
		os.system('sed -i '+ newr + ' ' + vis)
		os.system('sed -i '+ newt + ' ' + vis)

	else:
		print("Insufficent score, try again")

exit(level-1)

