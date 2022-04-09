all: build/aufgaben build/blatt0.pdf

build/aufgaben: aufgabe1.cpp aufgabe2.cpp aufgabe3.cpp | build
	g++ -o3 -Wall -ffast-math -march=native aufgabe1.cpp -o build/aufgabe1
	g++ -o3 -Wall -ffast-math -march=native aufgabe2.cpp -o build/aufgabe2
	g++ -o3 -Wall -ffast-math -march=native aufgabe3.cpp -o build/aufgabe3

build/blatt0.pdf: FORCE | build
	  TEXINPUTS=build: \
	  BIBINPUTS=build: \
	  max_print_line=1048576 \
	latexmk \
	  --lualatex \
	  --output-directory=build \
	  --interaction=nonstopmode \
	  --halt-on-error \
	blatt0.tex

build:
	mkdir -p build

clean:
	rm -rf build

FORCE:

.PHONY: all clean