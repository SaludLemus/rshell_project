CXX = g++
CXXFLAGS = -std=c++11 -c -Wall -Werror -ansi -pedantic
EXEC = rshell

SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(EXEC): $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(OBJECTS) -o $@

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: remove
remove:
	rm -r ./$(BINDIR)
	
.PHONY: clean
clean:
	rm -r ./$(OBJDIR)