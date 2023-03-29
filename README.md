# pyvicon-datastream-module
[![PyPI Downloads](https://img.shields.io/pypi/dm/pyvicon-datastream.svg?label=PyPI%20downloads)](
https://pypi.org/project/pyvicon-datastream/)


This module provides a **platform independent** python 3 wrapper implementation over the Vicon Datastream SDK.

**IMPORTATNT NOTICE:**
This module is currently still in development. So far I only managed to run and compile it on:
- **ARM**: M1 MacBook Pro with macOS Ventura 13.2.1
- **ARM**: M1-Pro MacBook Pro with macOS Ventura 13.2.1
- **ARM**: RaspBerry Pi 4 (4 GB) with Ubuntu 22
- **x86**: some Laptop with Ubuntu 20


### Background information
The python interface currently provided by Vicon itself (see https://docs.vicon.com/display/DSSDK111/Vicon+DataStream+SDK+Quick+Start+Guide+for+Python) only runs on Windows. Other solutions I found like the one from MathGaron https://github.com/MathGaron/pyvicon were only runnable on x86 and implied that you have to download a precompiled version (also there is currently no version available for ARM) of the library from the Vicon website and place it manually in your module.
So I created this module which ships with all the nescessary library sources and automatically compiles them on installation!



## Usage
### pyvicon_datastream
```
import pyvicon_datastream as pv

VICON_TRACKER_IP = "10.0.108.3"
OBJECT_NAME = "My_Object"

vicon_client = pv.PyViconDatastream()
ret = vicon_client.connect(VICON_TRACKER_IP)

if ret != pv.Result.Success:
    print(f"Connection to {VICON_TRACKER_IP} failed")
else:
    print(f"Connection to {VICON_TRACKER_IP} successful")
```

### Tools / ObjectTracker
```
from pyvicon_datastream import tools

VICON_TRACKER_IP = "10.0.108.3"
OBJECT_NAME = "My_Object"

mytracker = tools.ObjectTracker(VICON_TRACKER_IP)
while(True):
    position = mytracker.get_position(OBJECT_NAME)
    print(f"Position: {position}")
    time.sleep(0.5)
```


## Build / Install the Module

### Common issues when compiling / building the module:
- You need a C and C++ compiler on your system!
  - **Ubuntu / Linux:** `sudo apt install gcc g++`
  - **MacOS:** install the XCode Developer Tools
  - **Windows:** Install the Visual Studio C++ Development Tools (you will find installation info in the error message)

- fatal error: Python.h: No such file or directory
  - `sudo apt install python3-dev`









### The module ist available on PyPI!
`pip install pyvicon-datastream`

https://pypi.org/project/pyvicon-datastream/

### Local installation with sources
`pip install pyvicon-datastream-module/.`

For more information and output during install set the verbose flag: `-v`

`pip install pyvicon-datastream-module/. -v`

...somehow it's important to run the command from outside the main directory of the project (propably due to a naming conflict since inside the pyvicon-datastream-module folder there is (already) a folder called "pyvcion_datastream").

### Build / check
```
cd pyvicon-datastream-module
python -m build --sdist
twine check dist/*
```

## License Information
### PyVicon (wrapper implementation)
Files `pyvicon_datastream/pyvicon_datastream_wrapper.cpp` and `pyvicon_datastream/pyvicon_datastream.py` are from the project: https://github.com/MathGaron/pyvicon, a minimal python 3 wrapper implementation for the Vicon Datastream SDK.

License information see `pyvicon_datastream/LICENSE_PVICON_DATASTREAM`


### Vicon Datastream SDK
This Module ships with the Vicon Datastream SDK sources version 1.11.0.

Download Vicon Datastream SDK sources: https://github.com/whoenig/vicon-datastream-sdk

You can find the latest official version at https://vicon.com/downloads/utilities-and-sdk/datastream-sdk



## To Do's:
- ISSUE: BUILD FAILS on Windows!!!! Probably due to error with white spaces in path when trying to reference to .lib file
- Test on other Platforms: Windows
- Clean up Makefile
- Add examples
- Check if another source for downloading the Vicon Datastream SDK sources is available. At the moment the files are fenced behind a registration / email wall.
- Fix the "DOWNLOAD_EXTRACT_TIMESTAMP" warning / error message thrown by Cmake when fetching the boost lib sources zip from GitHub
