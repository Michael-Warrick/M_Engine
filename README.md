# M_Engine 
M_Engine is a cross-compilable, cross-developable real-time OpenGL rendered platform agnostic game engine written in C++, with an emphasis on performance.

## Table of Contents
1. [Introduction](#introduction)
2. [Setup](#setup)
3. [Running](#running)

## Introduction <a name="introduction"></a>
The best way to introduce this engine is to explain its purpose. It is as much of a demonstation of what can be achieved with modern approaches with C++ and OpenGL, using little to no overhead in order to achieve peak performace with maximal compatibility. Of course the sudden thought of compromised performance due to loose integration with platform specifics may cross one's mind, however, with the idea of opensource and inclusivity being predominant development factors, minimizing performance costs where they count and rigorously testing many differently specified configurations, will render any performance losses less noticeable.

## Setup <a name="setup"></a>
### IDE
Original development consisted of using a combination of Xcode and Visual Studio (not Code) for platform specific compilation with little to no insight on how to port to linux.

To remain platform agnostic, the choice of IDE was crucial. Hence the use of the recently developed (2015) IDE, Visual Studio Code, was chosen as a starting point. Below are links to download the program and the necessary steps to allow for syntax highlighting and compiling for C++.

**Visual Studio Code:** https://code.visualstudio.com/download
**Visual Studio Code - Getting Started:** https://code.visualstudio.com/docs/languages/cpp

### Compiler - GNU/MinGW
In order to run any code we must at some point compile to a specific platform due to the nature of C++, unlike java that compiles to bytecode and then runs in a VM or Python that's interpreted line by line, we need to compile the whole program and then run it. Platform specific links are available below.

**macOS:**
Simply download Xcode from the Mac App Store and clang will be intalled automatically or alternatively;
```shell
xcode-select --install
```

**Windows:**\
https://www.mingw-w64.org/

**Linux - Debian and Ubuntu 14.04+:** 
```shell
sudo apt-get install g++ -y
```
Now would be a good time to check if your platform specific compiler compiles just a simple `main.cpp` file. If everything is going smoothly so far, great! If not, consult Stackoverflow / Reddit.

### Cloning the repository
To get the project running on your machine either download it as a `.zip` and extract it or just:
```shell
git clone https://github.com/Michael-Warrick/M_Engine.git
```
If this isn't working, make sure you have git setup correctly (https://docs.github.com/en/get-started/quickstart/set-up-git)

## Running <a name="running"></a>
There is already a `.vscode` folder within the workspace meaning that it should be as simple as selecting the `launch.json` file as the desired compiler/launcher and hitting run.