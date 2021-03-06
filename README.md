# The Lightweight Object Oriented Structure analysis library

[![Build Status](https://travis-ci.org/GrossfieldLab/loos.svg?branch=master)](https://travis-ci.org/GrossfieldLab/loos)


## Getting Help
* New Releases: https://lists.sourceforge.net/lists/listinfo/loos-announce
* User Support: https://lists.sourceforge.net/lists/listinfo/loos-users
* Development:  https://lists.sourceforge.net/lists/listinfo/loos-devel

You can also contact us directly at loos.maintainer@gmail.com

## Documentation

Documentation is currently available online at http://loos.sourceforge.net
and bundled with the official release downloads.  If you are cloning from
GitHub, then local documentation will need to be built using Doxygen.
See the [INSTALL](INSTALL.md) file for more details.

## IMPORTANT NOTE FOR MACOS 10.11 "EL CAPITAN" USERS

There is a problem with using PyLOOS with the new System Integrity
Protection (SIP) enabled (see https://support.apple.com/en-us/HT204899
for more information about SIP).  We are aware of this and working on
a decent solution.  See the Mac section of the [INSTALL](INSTALL.md) file for more
details. 

## Using LOOS from GitHub

Welcome to the GitHub version of LOOS.  This repository was
created by converting our old SVN repository.  The SVN feature
branches exist as refs/tags, and appear in GitHub as releases,
but they should not be confused with the actual LOOS releases.  Those
can be found using semantic versioning (e.g. release-2.3.1,
release-2.3.0, ...)

We recommend that, unless you want to develop with LOOS, you
stick to downloading releases either by using tags, the releases tab
in GitHub, or downloading a release tarball from sourceforge.

For help with installing LOOS, please see the [INSTALL](INSTALL.md) file.  For
more details about what has changed in LOOS, see the [ChangeLog](ChangeLog) file.

### RELEASE 2.3.2

This release includes a number of changes to support our migration to
GitHub as well as some important bug fixes and additions.

We have reorganized the LOOS source code so that the core library now
resides in the "src" directory.  The shared library that's built (along
with the python code) is still copied to the top-level LOOS directory.

The Doxygen-based documentation is now handled a little bit differently.
When cloning from GitHub, the documentation will be automatically built
by SCons.  This means doxygen and graphviz are now required to build LOOS.
If you download a release from GitHub, then you can also download the pre-built
tar file containing the documentation.  If this is in the top LOOS
source directory, then SCons will see it and unpack it for you.  Finally,
if you download a release from SourceForge, the the pre-built documentation
is bundled with the release.  In all cases, you can always find the docs
for the current release online at http://grossfieldlab.github.io/loos/
or http://loos.sourceforge.net

Bugs fixed in this release include some important fixes to the OMG,
a bug affecting aligner and membrane_map when aligning to a reference
structure, making XTCWriter available to PyLOOS, and a few more minor
fixes.  See the [INSTALL](INSTALL.md) file for more details.

New tools in this release include verap, a quick vertical area profile
tool, cylindrical-thickness, and inside_helices.  New features include
providing support for manually mapping molecule names to segids in the
gmxdump2pdb tool and support for writing GRO files.


### RELEASE 2.3.1

This release of LOOS is a bug-fix release.  A bug was discovered in
membrane_map that caused the z-axis of all coordinates to be set to
0.  This affects height and vector calculations, but not density.

The build system has been changed slightly.  Some compilers require
multiple environment variables to work correctly.  In order to handle
these cases, the LOOS build will import all environment variables into
SCons before building.  This is *not* the SCons way to do things,
however it makes handling these edge cases much easier.  In the event
that these extra environment variables cause problems, you can revert
to a mostly "clean" build environment by editing the SConstruct file.
Starting at line 72 with "env = Environment(...)", uncomment the first
invocation and comment out the second one.

In addition, improvements were made to the documentation.




### RELEASE 2.3.0

This release of LOOS comes with a number of major changes, most
related to PyLOOS.  A detailed description of these changes is
available in the new "what's new in PyLOOS" section of the
documentation, and is listed in the "Quick Links" off the main page.

NUMPY IS NOW REQUIRED FOR BUILDING PYLOOS.  For Linux users, this will
just be a package install.  For Mac users, the system numpy will be
used.  See the [INSTALL](INSTALL.md) file for more information.

PyLOOS has been reorganized and new trajectory handling classes have
been added.  All Python-based components of PyLOOS are now in the
loos.pyloos module.  The new trajectory classes are easier to use than
the old PyTraj classes (they no longer require you to explicitly wrap
a loos.Trajectory object).  In addition, you can combine multiple
trajectories into a large "virtual" trajectory.  The frames of the
composite trajectory can be iteratively aligned (a la aligner) or
aligned to a reference structure.  See the documentation for pyloos
under the Namespace tab or search for Trajectory.

Additional PyLOOS changes include bug fixes for the iterativeAlignment
function.  The splitting functions in AtomicGroup now return a Python
list rather than an AtomicGroupVector.  Coordinates can be extracted
from an AtomicGroup or a Trajectory as a NumPy matrix.  An SVD/PCA
function has also been added to PyLOOS.  All old PyLOOS functions that
begin or end with Py are now deprecated and will be removed in the
next release.  These include PyTraj, PyAlignedTraj, and
iterativeAlignmentPy.  Finally, a k-means clustering program (using
PyLOOS) has been added.  Also, we've added a new package (Voronoi), which
will help users analyze membrane/membrane protein simulations.

There are a number of significant non-PyLOOS changes as well.  An
"index" keyword has been added to pick atoms based on their position
in a model (rather than atom id).  The rmsds tool (all-to-all RMSD)
has been significantly optimized and can now be run multithreaded.
The default is to use only a single thread.  If you built LOOS with a
multithreaded math library, be aware of possible conflicts (though
that shouldn't happen with rmsds).  Last, but not least, a number of
minor bug fixes are included.  See the ChangeLog file or the change
log in the documentation for more details.
