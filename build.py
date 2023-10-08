import sys
import os
import shutil
import subprocess
import multiprocessing
import glob

lib_name = "libmyplugin"
job_opt = " -j" + str(multiprocessing.cpu_count())

if "platform=windows" in sys.argv:
    subprocess.run("scons platform=windows bits=32 target=release" + job_opt, shell = True)
    subprocess.run("scons platform=windows bits=64 target=release" + job_opt, shell = True)

    os.makedirs("godot-proj/bin/windows", exist_ok = True)

    shutil.copy2(f"bin/{lib_name}.win32.dll", "godot-proj/bin/windows/")
    shutil.copy2(f"bin/{lib_name}.win64.dll", f"godot-proj/bin/windows/")

elif "platform=macos" in sys.argv:
    subprocess.run("scons platform=macos bits=64 target=release" + job_opt, shell = True)

    os.makedirs("godot-proj/bin/macos", exist_ok = True)

    shutil.copy2(f"bin/{lib_name}.macos.dylib", f"godot-proj/bin/macos/")

elif "platform=android" in sys.argv:
    subprocess.run("scons platform=android android_arch=armeabi-v7a target=release" + job_opt, shell = True)
    subprocess.run("scons platform=android android_arch=arm64-v8a target=release" + job_opt, shell = True)
    subprocess.run("scons platform=android android_arch=x86_64 target=release" + job_opt, shell = True)

    os.makedirs("godot-proj/bin/android", exist_ok = True)

    shutil.copy2(f"bin/{lib_name}.android.armeabi-v7a.so", f"godot-proj/bin/android/armeabi-v7a/{lib_name}.android.so")
    shutil.copy2(f"bin/{lib_name}.android.arm64-v8a.so", f"godot-proj/bin/android/arm64-v8a/{lib_name}.android.so")
    shutil.copy2(f"bin/{lib_name}.android.x86_64.so", f"godot-proj/bin/android/x86_64/{lib_name}.android.so")

elif "platform=ios" in sys.argv:
    subprocess.run("scons platform=ios ios_arch=arm64 target=release" + job_opt, shell = True)
    subprocess.run("scons platform=ios ios_arch=x86_64 target=release" + job_opt, shell = True)

    subprocess.run(f"lipo -create bin/{lib_name}.ios.arm64.dylib -output bin/{lib_name}.ios.dylib", shell = True)
    subprocess.run(f"lipo -create bin/{lib_name}.ios.x86_64.dylib -output bin/{lib_name}.ios-sim.dylib", shell = True)

    os.makedirs("godot-proj/bin/ios", exist_ok = True)
    
    shutil.copy2(f"bin/{lib_name}.ios.dylib", "godot-proj/bin/ios/")
    shutil.copy2(f"bin/{lib_name}.ios-sim.dylib", "godot-proj/bin/ios/")

elif "platform=web" in sys.argv:
    subprocess.run("scons platform=web bits=32 target=release" + job_opt, shell = True)

    os.makedirs("../Godot/addons/effekseer/bin/web", exist_ok = True)

    shutil.copy2(f"bin/{lib_name}.wasm", "godot-proj/bin/web/")
