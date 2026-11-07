# Vole machine simulator build
# Requirement 5: Separate compilation - headers, classes, and app are compiled separately.
# Requirement 6: Standard C++, no third-party libraries (no GUI).

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Application file per requirement 6: A2-YourSection-YourIDs.cpp
# Replace "Section" with your actual section number.
APP = A2-Section-20250814.cpp

# Class implementation files (separate compilation)
# NOTE: CPU.cpp, machine.cpp, InstructionDecoder.cpp, Instruction.cpp are teammates' files.
# Memory.cpp, Screen.cpp, Programs.cpp, A2-Section-20250814.cpp are Eslam's files.
SRCS = CPU.cpp machine.cpp Memory.cpp Screen.cpp Programs.cpp \
       InstructionDecoder.cpp Instruction.cpp ALU.cpp RegisterFile.cpp $(APP)

OBJS = $(SRCS:.cpp=.o)

TARGET = vole_sim

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
