# motion-sensor
Pi Pico with PIR sensor

# Wiring

Make sure to double check the wiring is correct and the buzzer/LED is oriented correctly. In motion.c you'll see more instructions of the specific GPIO used.


# Building

Make sure to have pico-sdk in a parellel directory to the motion directory containing this repo.

- mkdir build
- cd build
- cmake ..
- make

Then copy the motion.uf2 file over to the RP2040 while in flash mode (which can be set by holding BOOTSEL during connection with microusb)

Done!

# Live Demo
https://user-images.githubusercontent.com/41162160/185629441-34e504e5-d2d8-42e4-bfca-97833225cb1e.mp4

