import sys, platform

# Directories
TOOLS_DIR = "tools"
PREMAKE_DIR = "premake"
TARGET_DIR = "bin"
OBJ_DIR = "bin-obj"

# Solution and Project
ENGINE_NAME = "Alpha"
PROJECT_NAME = "AlphaEditor"

# Project Version
VERSION_MAJOR = 1
VERSION_MINOR = 0

# Platform and Configuration
PLATFORM = sys.platform
CONFIG = "Debug"

# Code Editor
VS_VERSION = "vs2019"


for x in platform.uname():
    p = x.lower()
    if "windows" in p:
        PLATFORM = "windows"
        break
    elif "linux" in p:
        PLATFORM = "linux"
        break
    elif "darwin" in p:
        PLATFORM = "darwin"
        break


def IsWindows():
    return PLATFORM == "windows"

def IsLinux():
    return PLATFORM == "linux"

def IsMac():
    return PLATFORM == "darwin"
