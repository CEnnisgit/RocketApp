CXX=g++
CXXFLAGS=-std=c++11 -Wall

SOURCES=main.cpp Rocket.cpp Telemetry.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TARGET=rocket_sim

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean
