# Schmitt_CSCI2270_FinalProject

	---TV Tracker Project--
developed by Jonathan Schmitt and Zachary Wilson starting 4/14/2015

Project Summary:
This is a c++ library designed to keep track of shows that a user intends to,
is in the process of, or has, watched holding these shows and their information
in the form of a struct and organizing them via a hash table for use as data.
As well the shows recorded and their hash table the project uses reference
pointers to allow sorting of the archive of shows without disorganizing the
hash table. Finally the library allows storing of information via a temp file
between instances or sessions.

How to Run:
No arguments are necessary upon using the constructor, from there adding and
removing shows from the archive are done with their respective functions.
Read from file should always be called upon startup of the program and write
to file should always be called upon the end so that the information can
be saved for use at a later time. Before using any of the sorting functions
sortSetup must be called, this will format a series of reference structs,
the head of which will be returned for the sort_Shows constructor. From there
all of the functions can be called and the list of reference structs can be
used. Ensure the destructor is called at the end of each use of the sorting
class to prevent memory leaks.

Dependencies:
The only nonstandard dependencies that the library uses is iostream so that it
can intereact with the temp file.

System Requirements:
The library is built on and for linux but uses standard libraries so any
conversion for use on Windows or Mac is solely a matter of interface. Also
the library's memory use is directly related to the number of shows in the
library so assuming a moderate number of shows are added the hardware required
to run is very low level.

Group Members:
Jonathan Schmitt
Zachary Wilson

Contributors:
none...yet

Open issues/bugs:
none...yet



The library is only dependant upon standard C++ libraries.

Use:

In order to run some memory and a processor are required, generally these
are no big deal if you've got-well-a computer.