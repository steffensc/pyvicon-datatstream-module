from skbuild import setup  # This line replaces 'from setuptools import setup'

setup(
    name="pyvicon_datastream",
    version="0.2-alpha",
    description="Platform independent minimal python 3 wrapper implementation over Vicon Datastream SDK",
    author="Steffen Schmelter",
    packages=["pyvicon_datastream"],
    url = 'https://github.com/steffensc/pyvicon-datatstream-module',
    install_requires=["numpy>=1.21"],
    python_requires=">=3.7",
)