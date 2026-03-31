#!/usr/bin/env python3
import subprocess
import shutil
import os
import sys

build_dir = os.environ["BUILD_DIR"]
pb_dir = os.environ["PB_DIR"]
library_file = "libpbloader.dll"
executable_file = "PerypetieBoba.exe"

if __name__ == "__main__":
    cmake_process = subprocess.run(["cmake", "--build", build_dir])
    if cmake_process.returncode != 0:
        print("cmake failed")
        sys.exit(1)

    library_path = f"{build_dir}/{library_file}"
    if os.path.isfile(library_path):
        shutil.copy(library_path, f"{pb_dir}/{library_file}")

        args = []
        if os.name == "nt":
            args = [executable_file]
        else:
            args = ["wine", executable_file]

        subprocess.run(args, cwd=pb_dir)
    else:
        print(f"Could not find {library_path}")
