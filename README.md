## tspress

A Qt app for tracking mouse/touchscreen pointer movements.

Used to evaluate a BeagleBone Black touchscreen.

Assuming Qt5 dev libraries and headers are already installed.

### Build natively

    $ qmake && make

### Operation

Run from a shell so you can see the output.

The UI places 5 buttons along the top of the screen.

Pressing the buttons will generate output to stdout.

You can test with a real USB mouse connected or by using the
touchscreen directly.

    
### Run under X11

Make sure you have calibrated the screen with *xinput_calibrator* first.

    $ export DISPLAY=:0.0
    $ xinput_calibrator

Then run the app

    $ export DISPLAY=:0.0 (if not already set)
    $ ./tspress


### Run without X

Not verified and needs some touchscreen libraries and utilities installed.

    $ ./tspress -platform linuxfb 

