# Makefile for Student Management System

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Target executable
TARGET = student_management

# Source files
SOURCES = student_management.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Install (copy to /usr/local/bin for system-wide access)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/
	sudo chmod +x /usr/local/bin/$(TARGET)

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

# Help
help:
	@echo "Available targets:"
	@echo "  all       - Build the program (default)"
	@echo "  clean     - Remove build files"
	@echo "  run       - Build and run the program"
	@echo "  install   - Install to system (requires sudo)"
	@echo "  uninstall - Remove from system (requires sudo)"
	@echo "  help      - Show this help message"

.PHONY: all clean run install uninstall help 