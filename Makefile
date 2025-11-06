CXX = g++
CXXFLAGS = -I./src/headers -I. -O2
TARGET = jake
OBJDIR = objs

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


clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean
