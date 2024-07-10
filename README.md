Below are the instructions to run download this application onto the MACs used in the Fermilab and Brookhaven Summer School.

First you will need to download the installation python script:

Login as admin onto the computer
Open a terminal

Install brew:
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Add brew to the path
```
(echo; echo 'eval "$(/opt/homebrew/bin/brew shellenv)"') >> /Users/admin/.zprofile
eval "$(/opt/homebrew/bin/brew shellenv)"
```

Obtain the installation script

Navigate to here and downlaod the file. It will probably ask you if you want to download it, just click download anyway

https://drive.google.com/file/d/1vH_byt7D5B5UdGLskfNSDcA-BJ_reRkQ/view?usp=sharing

Move the script to the right place
```
mv ~/Downloads/Rad_Demo_Install_1.2.4.py .
```

Execute it
```
python3 Rad_Demo_Install_1.2.4.py
```
This step takes a while so plug in the computer and find something better to do
There is no need to do a git clone on this repo, all that is handeled in the script


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Below are the instructions for instillation of a mac

This may or may not work

Obtain the installation script

Navigate to here and downlaod the file. It will probably ask you if you want to download it, just click download anyway

https://drive.google.com/file/d/16ItyHwOlNwuQpttO45y2sOB97VsYHypY/view?usp=sharing

Move the script to the right place
```
mv ~/Downloads/Rad_Demo_Install_2.0.py .
```

Execute it
```
python3 Rad_Demo_Install_2.0.py
```

You can execute it without any arguments but if you wish to install it in a certain place you can run it with arguments

```
python3 Rad_Demo_Install_2.0.py --home PATH_TO_DIRECTORY --install PATH_TO_DIRECTORY
```

This step takes a while so plug in the computer and find something better to do
There is no need to do a git clone on this repo, all that is handeled in the script

open a termnal, navigate to the install directory and execute
```
source Rad_Demo.sh
```
