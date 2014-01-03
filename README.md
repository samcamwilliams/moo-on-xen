moo-on-xen
==========

A COW programming language interpreter as an OS targeting the Xen hypervisor. Based on MiniOS (as included in the Xen source package). The OS is not built with a 'real' or complete libc library - only the one included in MiniOS.

moo-on-xen was built as a prototype for a much larger project, it is well and truly hacked together.

## Usage ##

**To run:**

From the repository directory, run the following:

```
# xm create domain\_config
```

**To build:**

The source must be placed in the 'extra' directory of an already configured and compiled Xen source tree. The system can then be built using `make` or the `build.sh` script (which will attempt to create a domain for the new OS after building, assuming a sane `sudo` installation).

## Future Work ##

There will not be any future work on this project, as it was just a quick hack on the way to something else. Feel free to work on it, if using useless languages as even more useless Operating Systems is your thing, though!
