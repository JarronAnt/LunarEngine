import globals
import os, sys, subprocess

args = globals.ProcessArguments(sys.argv)
CONFIG = globals.GetArgumentValue(args, "config", "debug")

print("Building config: " + CONFIG)
print("\n")
ret = 0

if globals.IsWindows():

    ret = subprocess.call(["cmd.exe", "/c", globals.VS_BUILD_PATH, "{}.sln".format(globals.ENGINE_NAME), "/property:Configuration={}".format(CONFIG)])

if globals.IsLinux():
    ret = subprocess.call(["make", "config={}".format(CONFIG)])

if globals.IsMac():
    ret = subprocess.call(["make", "config={}".format(CONFIG)])

sys.exit(ret)