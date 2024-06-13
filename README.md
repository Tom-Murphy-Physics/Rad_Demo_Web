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

Install cmake
```
brew install cmake
```

Obtain the installation script
Navigate to here and downlaod the file. It will probably ask you if you want to download it, just click download anyway

https://drive.google.com/file/d/17NXbVjoerFS41QCX7abOIio7jr67D6ej/view?usp=sharing

Move the script to the right place
```
mv ~/Downloads/Rad_Demo_Install_1.2.3.py .
```

Execute it
```
sudo python3 Rad_Demo_Install_1.2.3.py
```
This step takes a while so plug in the computer and find something better to do
There is no need to do a git clone on this repo, all that is handeled in the script

open a termnal and run
```
source Rad_Demo.sh
```
