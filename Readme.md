### All The Things (att)

## Description
Since moving back to Linux, I've found myself using multiple package managers to install software: apt, flatpak, guix, etc. I got tired of having to individually run updates on each, and I also wanted a way to search all of them for a single package to compare versions to make sure I got the latest version available among the managers. So that's when I decided to write All The Things (att)!

## Background
This is a program I'm writing mostly for my own usage. It is written in C and is based on the original [GNU Bash version](https://gist.github.com/echosa/390b968093c37e459ec38cd510d30de0) I wrote and use every day.

This project serves as a chance to dust off my C chops, which I've hardly used since college. If I get a personally useable program out of it, even better. If I get a program that others find useful, that'd be great as well.

Constructive criticism and tips for improvement are welcome. There's much about C I've forgotten, so I'm sure there are lots of things I can improve. Please share any improvements you find. Thanks!

## Supported Package Managers

`att` will only run for support package managers that you have installed. The current supported package managers are:
- apt
- brew
- flatpak
- guix
- snap

## Installation
I'm not providing any pre-built binaries at this time. Clone this repository, then run:
```
$ cmake -B build
$ cd build
$ make
$ sudo make install
```

## Usage
Using `att` is pretty straight forward. Examples include:

```
$ att search emacs # Search all managers for a package
$ att search --exact emacs # This is an exact search
$ att update # Update all managers
$ att upgrade # Upgrade all packages in all managers
$ att clean # Clean packages in all managers
$ att clean --managers=apt,flatpak # Only clean packages in apt and flatpak
$ att which # Show the output of `which` for all package managers
```

Note: Only package managers that are installed on your system will attempt to run, in order to reduce output and noise.

## Tests
Code checks can be run if [cppcheck](http://cppcheck.sourceforge.net/) is installed.
```
$ cmake -B build
$ cd build
$ make check
```
Tests can be run if [cmocka](https://cmocka.org) is installed.
```
$ cmake -B build
$ cd build
$ make test
```
