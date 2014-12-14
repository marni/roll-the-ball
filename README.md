# roll-the-ball


How can a map or terrain visualisation be done interactive on a mobile devices? 
This project is an exploration into terrain visualisation techniques and interactivity. 



## Folders structure

The initial folders example01 to example03 can be treated as a series of simple lessons to get 
going with Android NDK and  OpenGL ES programming on Android in a native format.  
Any feedback welcome!



### Example 01

Getting simple things sorted first.

	
	# To initiate the project from command line:

	android create project --target android-8 --name Example01 --path . --activity Example01 --package org.nzdis 


	# to build the debug version, and then install it on device

	ant debug 
	adb -d install -r bin/Example01-debug.apk


This project contains the skeleton of the OpenGL app, that does nothing. A perfect starting point ;)


### Example 02 and 03

This examples show the use of shaders to render a simple scene.



### sdl_simple

This is initial snapshot that uses SDL2 to render the same scene in a portable fashion so that the code can be cross-compile on all SDL supported platforms. 
The folder contains projects for Windows, MacOSX, iOS and Android.  It has been a proof-of-concept to demo the ability for cross-platform compilation.


### terrain_demo

This is an SFML-based demo.

