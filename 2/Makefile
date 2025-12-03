CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = main
SRCS = main.cpp DynamicArray.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q *.o $(TARGET).exe 2>nul || rm -f *.o $(TARGET)

.PHONY: all clean