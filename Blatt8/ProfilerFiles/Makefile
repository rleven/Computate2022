CXXFLAGS = -O3 -ffast-math -std=c++17 
HEADERS = profiler.h
SOURCES = profilerExample.cpp profiler.cpp

all: $(SOURCES) $(HEADERS)
	@g++ $(CXXFLAGS) $(SOURCES) -o profilerExample
	@./profilerExample
	
clean:
	@rm -f ./profilerExample

.PHONY: clean