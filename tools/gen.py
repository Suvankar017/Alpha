import globals
import subprocess, sys

res = 0

if globals.IsWindows():
    res = subprocess.call(["cmd.exe", "/c", "{}\\premake5".format(globals.PREMAKE_DIR), globals.VS_VERSION])
elif globals.IsLinux():
    res = subprocess.call(["{}/premake5.linux".format(globals.PREMAKE_DIR), "gmake2"])
elif globals.IsMac():
    res = subprocess.call(["{}/premake5".format(globals.PREMAKE_DIR), "gmake2"])
    if res == 0:
        res = subprocess.call(["{}/premake5".format(globals.PREMAKE_DIR), "xcode4"])

sys.exit(res)