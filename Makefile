BINDIR = bin
OBJDIR = obj
SRCDIR = src
SOURCES = $(shell find $(SRCDIR) -name *.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
INCLUDES = -I include/ -I /usr/local/include
SDLFLAGS = `pkg-config --libs --cflags sdl2`
CFLAGS = -lm #-Wall -Wextra -Werror
EXEC = asteroid

all : $(BINDIR) $(OBJDIR) $(SRCDIR) $(BINDIR)/$(EXEC)

$(BINDIR) :
	mkdir -p $(BINDIR)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	g++ $(SDLFLAGS) $(INCLUDES) $(CFLAGS) -c $(SRCDIR)/$*.cpp -o $(OBJDIR)/$*.o

$(BINDIR)/$(EXEC) : $(OBJECTS)
	g++ $^ $(SDLFLAGS) $(INCLUDES) $(CFLAGS) -o $(BINDIR)/$(EXEC) 

.PHONY: clean

clean:
	rm -f $(OBJDIR)/*
	rm -f $(BINDIR)/$(EXEC)