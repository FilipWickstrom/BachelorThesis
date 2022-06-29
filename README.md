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


# Thesis
https://www.diva-portal.org/smash/record.jsf?pid=diva2%3A1676868&dswid=-1403

## Visualization of the games
<img src="https://github.com/FilipWickstrom/BachelorThesis/blob/main/Images/Game1.PNG" width="50%"><img src="https://github.com/FilipWickstrom/BachelorThesis/blob/main/Images/Game2.PNG" width="50%">

## Specifications
|  System Under Test| 2                 | 5                       |
| ----------------- |:-----------------:|:-----------------------:|
| CPU name          | i7-8750h          | i7-8750h                |
| CPU speed (GHz)   | 4                 | 4                       |
| Cores             | 6                 | 6                       |
| Threads           | 12                | 12                      |
| Ram size (GB)     | 16                | 16                      |
| Ram speed (MHz)   | 2667              | 2667                    |
| OS                | Windows 10 (21H2) | Linux Ubuntu (20.04.4)  |

## Execution times
<img src="https://github.com/FilipWickstrom/BachelorThesis/blob/main/Images/ET_Game1_SUT2.png" width="50%"><img src="https://github.com/FilipWickstrom/BachelorThesis/blob/main/Images/ET_Game2_SUT2.png" width="50%">


## L1 cache misses
<img src="https://github.com/FilipWickstrom/BachelorThesis/blob/main/Images/L1_Game1_SUT5.png" width="50%"><img src="https://github.com/FilipWickstrom/BachelorThesis/blob/main/Images/L1_Game2_SUT5.png" width="50%">


## L3 cache misses
<img src="https://github.com/FilipWickstrom/BachelorThesis/blob/main/Images/L3_Game1_SUT5.png" width="50%"><img src="https://github.com/FilipWickstrom/BachelorThesis/blob/main/Images/L3_Game2_SUT5.png" width="50%">


# Libraries used
* [SFML](https://www.sfml-dev.org/)
* [OpenMP](https://www.openmp.org/)
* [EnTT](https://github.com/skypjack/entt)
