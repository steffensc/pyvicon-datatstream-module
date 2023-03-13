# pyvicon-datastream-module
IMPORTATNT NOTICE:
This module is currently still in development. So far I only managed to run and compile it on an M1 ARM MacBook Pro.


## Building/installing the module
`pip install pyvicon-datastream-module/.`

For more information and output during install set the verbose flag: `-v`

`pip install pyvicon-datastream-module/. -v`

…somehow it's important to run the command from outside the main directory of the project


## Usage




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
