import tools.globals
import os, sys, subprocess

def RunCommand(cmd):
    res = 0
    cmdScriptPath = "{}/{}/{}.py".format(os.getcwd(), tools.globals.TOOLS_DIR, cmd)

    if os.path.exists(cmdScriptPath):
        print("Executing :", cmd)
        res = subprocess.call(["py", cmdScriptPath])
    else:
        print("Invalid command :", cmd)
        res = -1

    print()
    return res

for i in range(1, len(sys.argv)):
    arg = sys.argv[i]
    
    print("---------------------------")
    if RunCommand(arg) != 0:
        break