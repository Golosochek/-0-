CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = dynamic_array_demo
SOURCES = main.cpp DynamicArray.cpp
HEADERS = DynamicArray.h

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean