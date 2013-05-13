mmcudemo
=======

This project contains some demonstration programs using mmculib (a
microcontroller independent library for common device drivers) and
mat91lib (an Atmel AT91SAM7 library).  The code is written to help my
students for their assignments but has not been rigourously tested so
caveat emptor!  

Since this project uses two submodules (mmculib and mat91lib), to
clone this project with version 1.6.5 of Git and later use:

    git clone --recursive git://github.com/mph-/mmcudemo.git

With earlier versions of Git use:

    git clone git://github.com/mph-/mmcudemo.git
    cd mmcudemo
    git submodule update --init

