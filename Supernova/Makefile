CXXFLAGS=-O3 -std=c++0x -Wall

SOURCES= $(wildcard *.cpp)

OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))

TARGET=$(lastword $(subst /, ,$(realpath .)))

LINKS= -lglut -lGL -lGLU

CXX=g++

all: $(TARGET)
	@echo Supernova built

$(TARGET): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) -o Supernova $(OBJECTS) $(LINKS)

clean:
	rm -rf $(OBJECTS) $(TARGET)
