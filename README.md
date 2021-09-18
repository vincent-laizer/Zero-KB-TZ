# Zero-KB-TZ
A simpler version of the infamous zero kb virus written in C++.  A few years back I was struck by the 'zero kb' virus, and so i decide to write my own zero kb virus as an act of vengeance ("kid you are an Avenger now").

## Usage:
This code was compiled using Dev-C++ IDE version 5, with an icon resource:
+ A folder icon ('icon.ico')
		
Target system: Windows OS Platform

## How it Works
:heavy_check_mark: When the program is executed, it copies it-self to the windows startup directory (C:\Users\<user name>\AppData\Roaming\Microsoft\Windows\Start Menu\Programs\Startup) thus, whenever the computer starts the code is also executed.

:heavy_check_mark: The program runs in background without any effect at first

:heavy_check_mark: Whenever an eternal storage device is connected, the program self-replicates into that drive and that triggers the harmfull part.

:heavy_check_mark: It deletes all the files present in the directories that are passed into the deleting function.

:heavy_check_mark: This Loop proceeds until the virus is detected and removed

## Whats Next?
* Any helpfull ideas are welcomed on how to improve the virus

## Caution
* it is important to remember:
  ````
  "With great power comes great responsibility."
  ````
