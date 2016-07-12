---
layout: default
title: Using Luna with your project
---

# Using Luna with your project

Luna is available from (and makes use of the) the [Conan](https://www.conan.io) dependency manager. And so should you.

To incorprate Luna into your project using Conan, simply add the following to your conanfile.txt:

    [requires]
    luna/1.0.0@DEGoodmanWilson/stable

Then run

    conan install --build=missing

(The `--build=missing` is because at the moment luna only offers source installs&emdash;we'll offer pre-built binaries before too long, just you see.)

(You can read more about usinc Conan with your project [in the Conan docs](http://docs.conan.io/en/latest/))