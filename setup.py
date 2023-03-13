from skbuild import setup  # This line replaces 'from setuptools import setup'

setup(
    name="pyvicon_datastream",
    version="0.1",
    description="",
    author="Steffen Schmelter",
    packages=["pyvicon_datastream"],
    #cmake_install_dir='src/hellosdfsdf',
    install_requires=["numpy>=1.21"],
    python_requires=">=3.7",
)