## tspress

A Qt app for tracking mouse/touchscreen pointer movements.

Used when working on Linux touchscreen drivers.

Assuming Qt5 dev libraries and headers are already installed.

### Build natively

    $ qmake && make

### Operation

The UI places 8 buttons along the edges of the screen.

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

    $ ./tspress -platform linuxfb -plugin evdevtouch

