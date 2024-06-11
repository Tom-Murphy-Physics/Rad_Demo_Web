Below are the instructions to run download this application onto the MACs used in the Fermilab and Brookhaven Summer School.

First you will need to download the installation python script:

Login as admin onto the computer
Open a terminal

Install brew:
```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Install wget
```
brew install wget
```

Obtain the installation script
```
wget --no-check-certificate 'https://docs.google.com/uc?export=download&id=1Lg_c09o3-xO2L-1HlvmcYsK43EpFLF8q' -O Rad_Demo_Install.py
```

Execute it
```
python3 Rad_Demo_Install.py
```
There is no need to do a git clone on this repo, all that is handeled in the script
