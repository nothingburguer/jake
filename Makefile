CXX = g++
CXXFLAGS = -I./src/headers -I. -O2
TARGET = jake
OBJDIR = objs

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

FLAG_MODULE_SRC = src/flags/modules
FLAG_MODULE_OBJ = $(OBJDIR)/help.o

OBJS = $(OBJDIR)/main.o $(OBJDIR)/parse_variables.o $(FLAG_MODULE_OBJ)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

$(OBJDIR)/help.o: $(FLAG_MODULE_SRC)/help.cpp $(FLAG_MODULE_SRC)/help.hpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/main.o: src/main.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/parse_variables.o: src/headers/parse_variables.cpp src/headers/parse_variables.hpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

install: $(TARGET)
	@echo "Installing $(TARGET) to $(BINDIR)"
	@install -d $(BINDIR)
	@install -m 755 $(TARGET) $(BINDIR)/$(TARGET)

uninstall:
	@echo "Removing $(BINDIR)/$(TARGET)"
	@rm -f $(BINDIR)/$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all install uninstall clean

