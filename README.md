# OpenMIMO

OpenMIMO is a header only library to implement dynamic system representation and control techniques.

It uses the Eigen(latest) project to implement all matrix logic and data structure

# Use OpenMIMO

to use OpenMIMO just

```
git clone --recursive https://github.com/bmarques1995/OpenMIMO.git
```

or add OpenMIMO as a submodule, because it is a header only API, you don't need to link it to your project.

To add OpenMIMO to your project, only include ./include and Eigen, that is already included as a submodule.

# Running unit tests

OpenMIMO uses **CMake 3.20 or later** to generate the test project, currently only works on linux distros, but will be added future support to MSVC. To generate the project run: 

```
cmake -S ./test -B <Build Directory>
```

## Running Code Coverage 

### Linux Distros

in the root directory, go to build directory and run Make(Linux) or open the generated Solution(Windows, MAC).

You can view the code coverage with gcov and gcovr, to get the code coverage run the tests program and in the make directory run:

```
gcovr -r <SourceRelativeDir> . --html --html-details -o <OutputHTMLFile>
```

to install gcov and gcovr just run:

```
sudo <package manager> gcov gcovr -y
```
