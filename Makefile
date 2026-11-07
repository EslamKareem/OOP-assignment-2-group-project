CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

APP = main.cpp
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
