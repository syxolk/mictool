OBJECTS = $(addprefix bin/,main.o io.o)
CXXFLAGS = -Wall -Wextra -Werror
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

bin/main.o : src/main.cpp src/io.h
bin/io.o : src/io.cpp
