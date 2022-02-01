import globals
import sys, subprocess

VS_BUILD_PATH = "C:\\\\Program Files (x86)\\\\Microsoft Visual Studio\\\\2019\\\\Community\\\\MSBuild\\\\Current\\\\Bin\\\\MSBuild.exe"

fullSolutionName = "{}.sln".format(globals.ENGINE_NAME)
configFlag = "/property:Configuration={}".format(globals.CONFIG.lower())
res = 0

if globals.IsWindows():
    if globals.IS_PARALLEL_BUILD:
        res = subprocess.call(["cmd.exe", "/c", VS_BUILD_PATH, fullSolutionName, "-m", configFlag])
    else:
        res = subprocess.call(["cmd.exe", "/c", VS_BUILD_PATH, fullSolutionName, configFlag])
elif globals.IsLinux():
    print("Linux is not supported currently... :(")
    res = -1
elif globals.IsMac():
    print("Mac is not supported currently... :(")
    res = -1

sys.exit(res)
