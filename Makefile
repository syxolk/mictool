OBJECTS = $(addprefix bin/,main.o io.o html.o)
CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -O3
EXECUTABLE = mictool

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)

.PHONY : all clean
all : $(EXECUTABLE)
clean :
	rm -f bin/*.o $(EXECUTABLE)

$(OBJECTS) : | bin

bin : 
	mkdir bin

bin/%.o : src/%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

bin/main.o : src/main.cpp src/io.h src/html.h
bin/io.o : src/io.cpp src/io.h
bin/html.o : src/html.cpp src/html.h src/io.h
