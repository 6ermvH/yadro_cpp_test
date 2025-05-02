CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Iinclude -g

SRCDIR := src
TESTDIR := tests
INCDIR := include
OBJDIR := obj

MAIN_TARGET := main
TEST_TARGET := test

SRC_FILES := $(wildcard $(SRCDIR)/*.cpp)
TEST_FILES := $(wildcard $(TESTDIR)/*.cpp)
OBJ_MAIN := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC_FILES))
OBJ_TEST := $(patsubst $(TESTDIR)/%.cpp,$(OBJDIR)/%.test.o,$(TEST_FILES))
OBJ_TEST += $(filter-out $(OBJDIR)/main.o, $(OBJ_MAIN))

all: $(MAIN_TARGET) $(TEST_TARGET)

$(MAIN_TARGET): $(OBJ_MAIN)
	$(CXX) $^ -o $@

$(TEST_TARGET): $(OBJ_TEST)
	$(CXX) $^ -o $@ -lpthread -lgtest -lgtest_main

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.test.o: $(TESTDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)
	rm -f $(MAIN_TARGET) $(TEST_TARGET)

.PHONY: all clean

