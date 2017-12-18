#the program assumes there is atleast pip and python installed
#this script is highly project specific....because it setups virtualenv
#which is used with python only.

#moreover it requires PhantomJS to be pre-installed
#further a better solution would be to setup vagrant using such a script
#future version of this tool will help setup vagrant using python

import platform
import subprocess
import os
import sys
from shutil import copyfile

# determine the OS on your system for automated development
operating_sys = platform.platform()
print type(operating_sys)

# check the error for each command by checking the size of error.txt...if it is greater than 0
# then report the error
def check_error(arg):
    result = (os.stat("error.txt").st_size == 0)
    if not result:
        with open("error.txt") as err:
            for line in err:
                print line
        print "Error using {}".format(arg)
        exit(-1)
    return

# check for a particular word in the output, to determine whether the command was run 
# successfully or not
def check_output(para):
    with open("output.txt") as opt:
        for line in opt:
            if para in line:
                return True
    return False

# Write requirements.txt file from a string
def write_requirements():
    text = "selenium==2.53.1" # write all your requirements here
    orig_stdout = sys.stdout
    f = open('requirements.txt','w')
    sys.stdout = f
    print text
    sys.stdout = orig_stdout
    f.close()

# create a copy of your source code in your virtual environment
def create_python_file():
    src = "" # path to source code on your system
    dst = "option2.py"
    copyfile(src,dst)

# creation of automated environment for development on linux
if "Linux" in operating_sys:
    #check whether virtualenv is pre-installed or not
    subprocess.call(['pip','list','>','output.txt','2>','error.txt'],shell=True)
    check_error("pip list")

    result = check_output("virtualenv")
    if not result:
        #install virtualenv if not installed already
        subprocess.call(['sudo','pip','install','virtualenv','>','output.txt','2>','error.txt'],shell=True)  
        check_error("pip install virtualenv")
        result = check_output("Successfully installed")
        if not result:
            print "Unable to install virtualenv"
            exit(-1)

    #set up virtualenv
    #delete error.txt and output.txt, because we are changing directory now
    os.remove("error.txt")
    os.remove("output.txt")
    subprocess.call(['virtualenv','pro_env','>','output.txt','2>','error.txt'],shell=True)
    check_error("virtualenv")
    result = check_output("done.")
    if not result:
        print "Unable to create virtual environment, check system manually"
        exit(-1)
    #activate it
    subprocess.call(['source','pro_env/bin/activate','2>','error.txt'],shell=True)
    check_error("activate command, check manually")
    #install requirements.txt
    write_requirements()
    subprocess.call(['sudo','pip','install','-r','requirements.txt','>','output.txt','2>','error.txt'],shell=True)
    #drawback here....sometimes dependencies installed with a warning....which goes into error.txt
    # check_error("pip install -r requirements.txt")
    #there exists a catch in the next statement, it doesn't checks just the last line in the file, which
    #indeed it should be doing
    result = check_output("Successfully installed")
    if not result:
        print "Unable to install dependencies"
        exit(-1)
    #install PhantomJS manually 
    create_python_file()
    subprocess.call(['python','option2.py','2>','error.txt'],shell=True)
    check_error("python option2.py")

    print "Execution complete"

# creation of automated environment for development on windows
elif "Windows" in operating_sys:
    #check whether virtualenv is pre-installed or not
    subprocess.call([r'\path\to\Scripts\pip','list','>','output.txt','2>','error.txt'],shell=True)
    check_error("pip list")

    result = check_output("virtualenv")
    if not result:
        #install virtualenv
        subprocess.call([r'\path\to\Scripts\pip','install','virtualenv','>','output.txt','2>','error.txt'],shell=True)  
        check_error("pip install virtualenv")
        result = check_output("Successfully installed")
        if not result:
            print "Unable to install virtualenv"
            exit(-1)

    #set up virtualenv
    #delete error.txt and output.txt, because we are changing directory now
    os.remove("error.txt")
    os.remove("output.txt")
    #cd to the directory where your project resides, in our case where option2.py and requirements.txt are present
    # subprocess.call(['cd','my_project','2>','error.txt'],shell=True)
    # check_error("cd") # can't do cd here
    subprocess.call([r'\path\to\Scripts\virtualenv','pro_env','>','output.txt','2>','error.txt'],shell=True)
    check_error("virtualenv")
    result = check_output("done.")
    if not result:
        print "Unable to create virtual environment, check system manually"
        exit(-1)
    #activate it
    subprocess.call([r'pro_env\Scripts\activate','2>','error.txt'],shell=True)
    check_error("activate command, check manually")
    #install requirements.txt
    write_requirements()
    subprocess.call(['pro_env\Scripts\pip','install','-r','requirements.txt','>','output.txt','2>','error.txt'],shell=True)
    #drawback here....sometimes dependencies installed with a warning....which goes into error.txt
    # check_error("pip install -r requirements.txt")
    #there exists a catch in the next statement, it doesn't checks just the last line in the file, which
    #indeed it should be doing
    result = check_output("Successfully installed")
    if not result:
        print "Unable to install dependencies"
        exit(-1)
    #install PhantomJS manually for windows
    create_python_file()
    subprocess.call(['pro_env\Scripts\python','option2.py','2>','error.txt'],shell=True)
    check_error("python option2.py")

    print "Execution complete"