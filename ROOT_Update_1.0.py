import os
import argparse

def attempt(command):
	try:
		os.system(command)
	except:
		print("Error: ", command)
		return False

def REMOVE_ROOT(ROOT_BUILD, ROOT_SRC):
	attempt("sudo rm -rf " + ROOT_BUILD)
	attempt("sudo rm -rf " + ROOT_SRC)
	return True

def ROOT(ROOT_SRC, ROOT_BUILD):
	attempt('cd')
	attempt('sudo git clone --branch latest-stable --depth=1 https://github.com/root-project/root.git ' + ROOT_SRC)
	attempt('sudo mkdir ' + ROOT_BUILD)
	attempt('sudo cd ' + ROOT_BUILD)
	attempt('sudo chmod 777 ' + ROOT_BUILD)
	attempt('cmake -B' + ROOT_BUILD + ' -S' + ROOT_SRC)
	attempt('sudo cmake --build ' + ROOT_BUILD + ' --target install')
	attempt('sudo source AFTERIMAGE-prefix')
	attempt('sudo . bin/thisroot.sh')
	return True

if __name__ == "__main__":

	HOME = "/Users/admin/"
	
	USER = os.path.expanduser("~")
	ROOT_BUILD = HOME + "root-build/"
	ROOT_SRC = HOME + "root_src/"
	
	Success = REMOVE_ROOT(ROOT_BUILD, ROOT_SRC)
	if Success == True:
		Success = ROOT(ROOT_SRC, ROOT_BUILD)
