OBJECTS = $(addprefix bin/,main.o)
CXXFLAGS = -Wall
EXECUTABLE = mikro

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)

.PHONY : all clean
all : $(EXECUTABLE)
clean :
	rm -f bin/*.o

$(OBJECTS) : | bin

bin : 
	mkdir bin

bin/%.o : src/%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

bin/main.o : src/main.cpp
