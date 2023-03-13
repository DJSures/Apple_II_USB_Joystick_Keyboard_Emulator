# Apple_II_USB_Joystick_Keyboard_Emulator
An Arduino Micro keyboard and Joystick emulator over USB. It emulates the keyboard as a real HID USB Keyboard. It also emulates a Joystick in either Mouse or Joystick mode. Shortcut keys change the mode.

Live hack 1: https://www.youtube.com/live/l9JXFGYm8Pk
Live hack 2: https://www.youtube.com/live/UXvmlQU1Qzs
Playing games: https://www.youtube.com/live/Q85PDDTFcNY
Overview: https://www.youtube.com/watch?v=vekLtMoc8dY

Keyboard PCB

![image](https://user-images.githubusercontent.com/49293683/224582328-084d8861-73e0-4154-a644-0f4036c24c04.png)

![image](https://user-images.githubusercontent.com/49293683/224582356-30af5be6-6d61-473c-a7b1-181f1d932f8c.png)




# Joystick Modes
The shortcut keys can change the joystick mode. By default, the joystick emulates a mouse USB device. Pressing CTRL-Z twice will beep the speaker and change the joystick between USB mouse and USB joystick modes

# Keyboard Modes
The shortcut keys CTRL-A twice will change the number pad between cursor keys or numbers. Of course, your keyboard of an authentic Apple II won't have this magical number pad. A clone will! 

# ALT-F4 Shortcut
I made a shortcut for pressing ALT-F4 on the keyboard, by hitting CTRL-Q twice. The reason was to close the foreground application on my Apple quickly.

# Sound
To receive the startup beep and shortcut key combination beeps, connect a speaker to pin #16

# What emulator?
I originally had a Raspberry Pi in the apple hack, which used Retro Pi and Linapple. However, Linapple is okay but doesn't have reliable sound... Specifically no mockingboard or phaser sound! While the author accepts that limitation, I prefer to have audio on my emulated apple ii. So, the solution was AppleWin on Windows. I replaced the Raspberry pi with an Atomic Pi. The Atomic Pi is x86 and by also being considerably more powerful can run Windows 10.

