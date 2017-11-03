CC = g++
CC_FLAGS = -Wall -Werror -ansi -pedantic
EXEC = rshell

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(EXEC): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CC) $(OBJECTS) -o $@

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CC) -c $(CC_FLAGS) $< -o $@

.PHONY: remove
remove:
	rm -r ./$(BINDIR)
	
.PHONY: clean
clean:
	rm -r ./$(OBJDIR)