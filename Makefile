BINDIR = bin
OBJDIR = obj
SRCDIR = src
SOURCES = $(shell find $(SRCDIR) -name *.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
INCLUDES = -I ./include/ -I /usr/local/include
SDLFLAGS = -lSDL2
CFLAGS = -lm #-Wall -Wextra -Werror
EXEC = asteroid
LD_LIBRARY_PATH="./lib"

all : $(BINDIR) $(OBJDIR) $(SRCDIR) $(BINDIR)/$(EXEC)

$(BINDIR) :
	mkdir -p $(BINDIR)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	g++ $(SDLFLAGS) $(INCLUDES) -L./lib $(CFLAGS) -c $(SRCDIR)/$*.cpp -o $(OBJDIR)/$*.o

$(BINDIR)/$(EXEC) : $(OBJECTS)
	g++ $^ $(SDLFLAGS) $(INCLUDES) -L./lib $(CFLAGS) -o $(BINDIR)/$(EXEC) 
	@echo "\n################\nPlease use make run to execute\n################"

.PHONY: clean run

run: $(BINDIR)/$(EXEC)
	LIBGL_DEBUG=verbose LD_LIBRARY_PATH=./lib $(BINDIR)/$(EXEC)

clean:
	rm -f $(OBJDIR)/*
	rm -f $(BINDIR)/$(EXEC)