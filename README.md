roll-the-ball
=============

The main idea is to implement a system that allows novel ways of experiencing terrain on mobile devices. The initial task is designed to be: Rolling the ball on a terrain. 
The project hopes to explore new way of interacting with maps.


Educational purpose
===================

This repo is organized as a series of lessons to get going with Android NDK and 
OpenGL ES programming on Android in a native format.  Try to follow. Any feedback welcome!



* Example 01

Getting simple things sorted first.

	
	# To initiate the project from command line:

	android create project --target android-8 --name Example01 --path . --activity Example01 --package org.nzdis 


	# to build the debug version, and then install it on device

	ant debug 
	adb -d install -r bin/Example01-debug.apk


This project contains the skeleton of the OpenGL app, that does nothing. A perfect starting point ;)

