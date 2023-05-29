import PySimpleGUI as sg

g1 = r'./gifs/facepalm.gif'
gifs = [g1]
layout = [[sg.Image(background_color='white', key='-IMAGE-', right_click_menu=['UNUSED', 'Exit'])],[sg.Text('sAmPlE TexT',key='smptex')]]

window = sg.Window('Title',layout, finalize=True)
image =  window['-IMAGE-']               #type: sg.Image
counter = 0
while counter<100:
    event, values = window.read(timeout=100)
    if event == 'Exit':
        break
    else:
	    image.update_animation(g1, 100)
    counter += 1
