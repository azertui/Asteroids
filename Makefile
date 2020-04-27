BINDIR = bin
OBJDIR = obj
SRCDIR = src
SOURCES = $(shell find $(SRCDIR) -name *.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
INCLUDES = -I ./include/ -I /usr/local/include
SDLFLAGS = -lSDL2 -lSDL2main
CFLAGS = -lm
EXEC = asteroid
LD_LIBRARY_PATH="./lib"
DFLAGS = -Wall -Wextra -Werror -ggdb3

all : lib include/SDL2 $(BINDIR) $(OBJDIR) $(SRCDIR) $(BINDIR)/$(EXEC)

lib:
	./install.sh

include/SDL2:
	./install.sh

$(BINDIR) :
	mkdir -p $(BINDIR)

$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	g++ $(SDLFLAGS) $(INCLUDES) -L./lib $(CFLAGS) -c $(SRCDIR)/$*.cpp -o $(OBJDIR)/$*.o

$(BINDIR)/$(EXEC) : $(OBJECTS)
	g++ $^ $(SDLFLAGS) $(INCLUDES) -L./lib $(CFLAGS) -o $(BINDIR)/$(EXEC) 
	@echo "\n################\nPlease use make run to execute\n################"

.PHONY: clean run cleanAll install debug_compile debug

run: all
	LIBGL_DEBUG=verbose LD_LIBRARY_PATH=./lib $(BINDIR)/$(EXEC)

debug: clean debug_compile
	$(CFLAGS) = $(CFLAGS) + " -Wall -Wextra -Werror -ggdb3"
	$(MAKE) all
	LIBGL_DEBUG=verbose LD_LIBRARY_PATH=./lib gdb $(BINDIR)/$(EXEC)

debug_compile: CFLAGS+=$(DFLAGS)
debug_compile: all;

clean:
	rm -f $(OBJDIR)/*
	rm -f $(BINDIR)/$(EXEC)

cleanAll: clean
	rm -rf build lib share $(BINDIR)/sdl2-config include/SDL2

install:
	./install.sh