# MetaReflect

Metareflect is a lightweight reflection system for C++, based on LLVM and Clangs
libtooling.

- **Lookup members of reflected classes:** Once reflection data has been generated,
you can query the members of the class, inspect their types, size and where they're
located in the class, as well as qualifiers and storage class.
- **Control over which classes are reflected:** By annotating your class with
`CLASS`, and each member which you want to be reflected with `PROPERTY`, you
have fine-grained control over what you want to reflect, and what you want to
keep completely private.
- **Extensible:** It's easy to add new flags, which can be queried at runtime.
This allows for easily adding any feature you like. Currently used to provide
serialization from and to a byte stream for annotated classes.


# Getting Started

**To get started [download the latest release here](/releases).**

## Setting Up The Runtime

Metareflect requires the runtime, it's consisting of the interface and a couple
helper macros for annotating your classes. To include it into your project,
simply copy over the [`/metareflect`](/metareflect) folder into your project.
Unfortunately, the runtime is not fully header-only and requires you to compile
the files ending in `.cxx`.


## Annotating Your Classes

Every class which you want to be reflected needs to be annotated.

**point.hxx:**

    #include <metareflect/metareflect.hxx>

    CLASS() Point
    {
    public:
        PROPERTY()
        int x;

        PROPERTY()
        int y;

        PROPERTY()
        int z;

        FUNCTION()
        size_t Hash() const
        {
            return x ^ y ^ z;
        }
    };

**point.cxx:**

    #include "point.hxx"
    #include "point.generated.hxx"

    /* rest of the code */


For a full example take a look at our [`/example`](/example).

## Run The Metareflect Tool

To provide the reflection data, the metareflect tool generates a header-file
which contains the reflection data in a format consumable by the runtime.
The generated file needs to be in your include path and included into the
implementation file of the reflected class.

Since metareflect is based on libtooling, all the flags common to libtooling
tools apply to it to. That means if you have a build system which can generate
a `compile_commands.json` (for example: ninja or CMake) you can simply provide
it the path to your compilation database and metareflect will pick the correct
flags automatically.
For further information, consult the [LLVM documentation for libtooling](https://clang.llvm.org/docs/HowToSetupToolingForLLVM.html).

To generate a compilation database using CMake, pass it
`-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` while generating your build files.


# Contributing

Any contribution is welcome. Take a look at the [open tickets](/issues) to get
started with the development of metareflect.

## Requirements

- A clone of the LLVM 6.0.0 source code, including clang and clang-extra-tools.
  See [LLVM_SETUP](/LLVM_SETUP.md) how to setup LLVM for development.
- A clone of the metareflect repository
- A beefy computer, otherwise compiling LLVM will take some time

## Structure

Metareflect consists of two parts, the runtime and the libtooling tool.

The runtime lives in the `metareflect/` folder, while the `tooling/` folder
contains the source code for the tool.

## Getting Started

Once you've cloned the LLVM repo (by following the guide at [LLVM_SETUP](/LLVM_SETUP.md)),
navigate to `path/to/llvm/tools/clang/tools/extra/metareflect/metareflect`.
The directory contains the source code for metareflect and anything you need
to get started developing metareflect.

The following resources give an insight into how to develop an libtooling application:

- [Clang Documentation on LibTooling](https://clang.llvm.org/docs/LibTooling.html)
- [Using ASTMatchers in LibTooling](https://clang.llvm.org/docs/LibASTMatchersTutorial.html)

To contribute your changes back, please open a pull request! We welcome any contribution.

# Inspiration

Parts of the design and how the tool works has been based upon prior research
done in Unreal Engine 4s UHT (Unreal Header Tool) and Qts `moc`.
If you've used either of the two, you might spot the similarities.

# License

[MIT License](/LICENSE)

Copyright (c) 2018 Arvid Gerstmann.

