# pyvicon-datastream-module
This module provides a platform independent minimal python 3 wrapper implementation over Vicon Datastream SDK.

**IMPORTATNT NOTICE:**
This module is currently still in development. So far I only managed to run and compile it on an M1 ARM MacBook Pro.

The python interface currently provided by Vicon itself (see https://docs.vicon.com/display/DSSDK111/Vicon+DataStream+SDK+Quick+Start+Guide+for+Python) only runs on Windows. Other solutions I found like the one from MathGaron https://github.com/MathGaron/pyvicon were only runnable on x86 and implied that you have to download a precompiled version (also there is currently no version available for ARM) of the library from the Vicon website and place it manually in your module.
So I created this module which ships with the nescessary library sources and automatically compiles them on installation.


## Build / Install the Module
`pip install pyvicon-datastream-module/.`

For more information and output during install set the verbose flag: `-v`

`pip install pyvicon-datastream-module/. -v`

…somehow it's important to run the command from outside the main directory of the project


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

### ObjectTracker
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


## License Information
### PyVicon (wrapper implementation)
Files `pyvicon_datastream/pyvicon_datastream_wrapper.cpp` and `pyvicon_datastream/pyvicon_datastream.py` are from the project: https://github.com/MathGaron/pyvicon, a minimal python 3 wrapper implementation for the Vicon Datastream SDK.

License information see `pyvicon_datastream/LICENSE_PVICON_WRAPPER`


### Vicon Datastream SDK
This Module ships with the Vicon Datastream SDK sources version 1.11.0.

Download Vicon Datastream SDK sources: https://github.com/whoenig/vicon-datastream-sdk

You can find the latest official version at https://vicon.com/downloads/utilities-and-sdk/datastream-sdk


### Boost
Installing Boost Lib
- MacOS:
  - If not present install *homebrew* on MacOS (https://brew.sh)
  - `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`
  - `brew install boost`

- Linux:

- Windows:

TODO: Ship Boost sources with package, so installation of libs is not necessary
- https://github.com/boostorg/system
- https://github.com/boostorg/thread
- https://github.com/boostorg/timer
