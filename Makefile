CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -O3
EXECUTABLE = mictool
CXX = g++
BIN = bin
OBJECTS = $(addprefix $(BIN)/,main.o io.o html.o)

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)

.PHONY : all clean
all : $(EXECUTABLE)
clean :
	rm -f $(BIN)/*.o $(EXECUTABLE)

$(OBJECTS) : | $(BIN)

$(BIN) : 
	mkdir $(BIN)

$(BIN)/%.o : src/%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

$(BIN)/main.o : src/main.cpp src/io.h src/html.h
$(BIN)/io.o : src/io.cpp src/io.h
$(BIN)/html.o : src/html.cpp src/html.h src/io.h
