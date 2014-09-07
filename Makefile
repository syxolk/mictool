CXXFLAGS = -Wall -Wextra -Werror -std=c++0x -O3
EXECUTABLE = mictool
CXX = g++
BIN = bin
OBJECTS = $(addprefix $(BIN)/,main.o io.o html.o util.o)
INSTALLDIR = /usr/local/bin
MANDIR = /usr/local/share/man/man1

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJECTS)

.PHONY : all clean install
all : $(EXECUTABLE)
clean :
	rm -f $(BIN)/*.o $(EXECUTABLE)
install : all $(INSTALLDIR)/$(EXECUTABLE) $(MANDIR)/$(EXECUTABLE).1.gz

$(INSTALLDIR)/$(EXECUTABLE) : $(EXECUTABLE)
	cp ./$(EXECUTABLE) $(INSTALLDIR)/$(EXECUTABLE)

$(MANDIR)/$(EXECUTABLE).1.gz : $(EXECUTABLE).1.gz
	mkdir $(MANDIR)
	cp $(EXECUTABLE).1.gz $(MANDIR)/$(EXECUTABLE).1.gz

$(EXECUTABLE).1.gz : $(EXECUTABLE).1
	gzip --keep --force $(EXECUTABLE).1

$(OBJECTS) : | $(BIN)

$(BIN) : 
	mkdir $(BIN)

$(BIN)/%.o : src/%.cpp
	$(CXX) -c $(CPPFLAGS) $(CXXFLAGS) $< -o $@

$(BIN)/util.o : src/util.cpp src/util.h
$(BIN)/main.o : src/main.cpp src/io.h src/html.h
$(BIN)/io.o : src/io.cpp src/io.h src/util.h
$(BIN)/html.o : src/html.cpp src/html.h src/io.h src/util.h

