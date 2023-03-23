from skbuild import setup  # This line replaces 'from setuptools import setup'
from pathlib import Path


setup(
    name="pyvicon_datastream",
    version="0.2.1",
    description="Platform independent Python3 wrapper for Vicon Datastream SDK",
    author="Steffen Schmelter",
    packages=["pyvicon_datastream"],
    project_urls={
            "Source Code": "https://github.com/steffensc/pyvicon-datatstream-module",
        },
    download_url="https://pypi.org/project/pyvicon-datastream",
    platforms=["Windows", "Linux", "Mac OS-X", "Unix"],
    install_requires=["numpy>=1.21"],
    python_requires=">=3.7",
    long_description=Path("README.md").read_text(encoding="utf-8"),
    long_description_content_type="text/markdown",
)