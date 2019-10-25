# Setting Up LLVM

Setting up LLVM can be quite hairy. This should guide you through the necessary
steps to get LLVM up and running to develop metareflect.

# Requirements

- Around 20 GB of free disk space
- A powerful computer (or some time)

# Cloning LLVM

1. Clone LLVM

```
git clone https://git.llvm.org/git/llvm.git/ llvm
```

2. Clone Clang
```
cd llvm/tools
git clone https://git.llvm.org/git/clang.git/ clang
```

3. Clone Clang-Extra-Tools
```
cd clang/tools
git clone http://llvm.org/git/clang-tools-extra extra
```

3. Clone Metareflect
```
cd extra
git clone https://github.com/Leandros/metareflect.git metareflect
```

4. Add Metareflect to CMakeLists.txt (assuming a posix shell)
```
echo "add_subdirectory(metareflect/tooling)" >> CMakeLists.txt
```

# Building LLVM

The following assumes you're working on Windows using Visual Studio.
The steps are similar for *nix-like operating systems, simply switch out
the Visual Studio CMake generator with `ninja`.

1. Generating CMake Build
```
cd path/to/llvm/root
mkdir build
cd build
cmake .. -G"Visual Studio 2017 Win64"
```

2. Open the resulting Visual Studio project

**You're all set!**
Navigate to the `metareflect` project to get started with development.

