RemoteSwitch library v2.0.0 (20100130) for Arduino 0017
Made by Randy Simons http://randysimons.nl

This library provides an easy class for Arduino, to send and receive signals
used by some common 433MHz remote control switches

See RemoteSwitch.h for details!

License: "Free BSD license". See ./RemoteSwitch/license.txt


Installation of library:
-Make sure Arduino is closed
-Copy the directory RemoteSwitch to the Arduino library directory (usually
 <arduinodir>/hardware/libraries/)
 
Default installation sender & demo:
-Connect tha data-in-pin of a 433MHz transmitter to digital pin 11. See photo.
 (Note: your hardware may have a different pin configuration!)
-Start Arduino, and open the example: File -> Examples -> RemoteSwitch ->
 Light_show
-Alter addresses/devices to reflect your own setup. Otherwise nothing will
 happen.
-Compile, upload and run!

Default installation receiver & demo
-Connect the data-out-pin of a 433MHz receiver to digital pin 2. See photo.
 (Note: your hardware may have a different pin configuration!)
-Start Arduino, and open the example: File -> Examples -> RemoteSwitch ->
 Show_received_code
-Compile, upload and run
-Open serial monitor in Arduino (115200 baud)
-Press buttons on a 433MHz-remote, and watch the serial monitor
