### All The Things (att)

## Description
Since moving back to Linux, I've found myself using multiple package managers to install software: apt, flatpak, guix, etc. I got tired of having to individually run updates on each, and I also wanted a way to search all of them for a single package to compare versions to make sure I got the latest version available among the managers. So that's when I decided to write All The Things (att)!

## Background
This is a program I'm writing mostly for my own usage. It is written in C and is based on the original [GNU Bash version](https://gist.github.com/echosa/390b968093c37e459ec38cd510d30de0) I wrote and use every day.

This project serves as a chance to dust off my C chops, which I've hardly used since college. If I get a personally useable program out of it, even better. If I get a program that others find useful, that'd be great as well.

Constructive criticism and tips for improvement are welcome. There's much about C I've forgotten, so I'm sure there are lots of things I can improve. Please share any improvements you find. Thanks!

## Installation
I'm not providing any pre-built binaries at this time. In order to use `att`, clone or download this repository, then run `make`. You can use the resulting `att` binary.

## Usage
Using `att` is pretty straight forward. Examples include:

```
$ att search emacs # Search all managers for a package
$ att search --exact emacs # This is an exact search
$ att upgrade # Update and upgrade all packages in all managers
$ att clean # Clean packages in all managers
```

Note: Only package managers that are installed on your system will attempt to run, in order to reduce output and noise.
