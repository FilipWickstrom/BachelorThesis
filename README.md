# Performance comparison between OOD and DOD with multithreading in games

This is a bachelor thesis written by Filip Wickström and David Wingqvist. 
Here we compare two design patterns within the scope of games.
The two design patterns are:
* OOD - Object-oriented design
* DOD - Data-oriented design

Two different games was developed and can be seen in different folders.
* Game 1: Uses OOD and DOD with a self-written ECS. Is also using multithreading (OpenMP) for the two patterns.
* Game 2: Uses OOD and DOD with the ECS library [EnTT](https://github.com/skypjack/entt)

# How to compile & run
Windows: Build the visual studio project with "buildVS.bat". 
It is building for VS2019, but can be easily changed to other versions of VS as well if needed.
Run the program in visual studio in "release" for best performance.

Linux: Use the command "make" to build the game.
This command will create the executable file "BachelorThesis" that can be started by "./BachelorThesis".
If the program is not compiling you might need to download SFML and the command is mentioned in the makefile.

# In project
You can play around with different values in the "PCH.h" files for the games to see the differences between the two design patterns.


# Final thesis
https://www.diva-portal.org/smash/record.jsf?pid=diva2%3A1676868&dswid=-1403


# Libraries used
* [SFML](https://www.sfml-dev.org/)
* [OpenMP](https://www.openmp.org/)
* [EnTT](https://github.com/skypjack/entt)
