Introduction
============

OpenVSIP uses a build system that is based on the GNU autotools. A typical build process thus consists of executing `configure`, `make`, and `make install`. The individual steps are discussed in detail below.

Prerequisites
=============

OpenVSIP can be compiled for a variety of target platforms, including x86, ppc, and cuda. 
It relies on (partly optional) third-party libraries for specific computational kernels:

* [FFTW](http://www.fftw.org/)
* [LAPACK](http://www.netlib.org/lapack/)
* [OpenMPI](https://developer.nvidia.com/cuda-toolkit)
* [CUDA](https://developer.nvidia.com/cuda-toolkit)

OpenVSIP is known to compile with [G++](http://gcc.gnu.org/), version 4.4 and higher.
It is being developed on Fedora.

Testing and benchmarking requires

* [Python](http://python.org/)
* [QMTest](http://mentorembedded.github.io/qmtest/)

Configuration
=============

To configure OpenVSIP:

     % mkdir objdir
     % cd objdir
     % srcdir/configure [options]

Useful options:

 * `--prefix=dirname` : Specify the toplevel installation directory.
                        (The default is `/usr/local`.)
 * `--enable-parallel` : Enable support for the Parallel VSIPL++ API.
 * `--enable-lapack=<lapack>` : Enable LAPACK bindings using the specified backend.
 * `--enable-fft=<fft-backend-list>` : Enable the specified FFT backends.


Building
========

To build OpenVSIP:

     % make

Testing
=======

To run the OpenVSIP test suite:

     % make check

(To run tests in parallel, use `make check parallelism=<n>` 
with the specified concurrency level.)

Installing
==========

To install OpenVSIP:

     % make install

This will install OpenVSIP in the prefix specified during configuration.

Running Examples
================

OpenVSIP contains a number of example applets that demonstrate how to
use specific APIs. To build them, start by setting up an OpenVSIP workspace:

    % $(prefix)/bin/openvsip-create-workspace ovxx-workspace

Within the 'ovxx-workspace' directory structure you can now run `make` 
(or `make <target>`) to build the demo apps. Make sure to set your environment 
variables (notably LD_LIBRARY_PATH) so that the appropriate libraries are found.