#config = 'release'
#arch = 'i686'
import os
imageType = 'floppy'
imageFS = 'fat32'
imageSize = '250m'
toolchain='../toolchains'
if not os.path.exists(toolchain):
    os.mkdir(toolchain)
toolchain=os.path.abspath(toolchain)
