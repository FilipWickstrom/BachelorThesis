CXX 		= g++

#Debug
#	-g 		: tells compiler to save debugging information
# 	-Wall	: shows all warnings
#CXXFLAGS 	= -g -Wall -std=c++17

#Release
#	-o2 	: optimizing with compiler
CXXFLAGS 	= -std=c++17 -o2

SOURCEPATH = Engine/src
SOURCE 	:= $(wildcard $(SOURCEPATH)/*.cpp)
OBJECTS := $(patsubst %.cpp, %.o, $(SOURCE))	


#Install on linux via: 	"sudo apt-get install libsfml-dev"
#Install openmp via:	"sudo apt-get install libomp-dev"
DYNAMICLIBS = -lsfml-graphics -lsfml-window -lsfml-system -fopenmp


game: $(OBJECTS)
		$(CXX) $(CXXFLAGS) -o BachelorThesis $(OBJECTS) $(DYNAMICLIBS)

$(SOURCEPATH)/%.o: $(SOURCEPATH)/%.cpp
		$(CXX) $(CXXFLAGS) -c $< -o $@ -fopenmp


clean:
	rm -f $(OBJECTS) BachelorThesis

