# KeyGrab

## Introduction
**DO NOT USE ON SYSTEMS WITHOUT EXPLICIT PERMISSION
> KeyGrab is a program designed for experienced users to automate WiFi testing. Similar programs do not save the files you intercept, and begin attempting to check against wordlists. This is a problem when running these on under-powered systems or laptops.


>KeyGrab collects capture files, converts them into hccapx files, and organizes them in folders. These can then be used in conjunction with programs like Hashcat to crack the handshake files.

## Installation

> Check the source code! KeyGrab.c will contain macros specific to my system. They might work on others, however, I can't test them all. This is extremely easy to make compatible. Just change the macros up top to your wireless card info.

> Simply run "make". This will create executables and let you run KeyGrab as well as the capture conversion tool made by the Hashcat developers.

>Run "./KeyGrab" to get started. Use ctrl+c to step through when needed.
