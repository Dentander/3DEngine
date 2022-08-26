import shutil
import sys


class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


try:
    # Source path
    src = sys.argv[1] + "/engine/graphics/glsl"

    # Destination path
    dest = sys.argv[2] + "/glsl"

    try:
        shutil.rmtree(dest)
    except:
        pass

    shutil.copytree(src, dest, True)

    print(bcolors.OKBLUE + "========= GLSL folder successfully copied! =========" + bcolors.ENDC)

except:
    print(bcolors.FAIL + "======== Failed to copy GLSL folder! ========" + bcolors.ENDC)
