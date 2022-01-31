import globals
import os, subprocess, sys

exePath = "{}/{}/{}/{}/".format(os.getcwd(), globals.TARGET_DIR, globals.CONFIG, globals.PROJECT_NAME)
exeFullPath = "{}{}".format(exePath, globals.PROJECT_NAME)
res = 0

if globals.IsWindows():
    res = subprocess.call([exeFullPath], cwd=exePath)
elif globals.IsLinux():
    print("Linux is not supported currently... :(")
    res = -1
elif globals.IsMac():
    print("Mac is not supported currently... :(")
    res = -1

sys.exit(res)
