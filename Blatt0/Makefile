all: aufgaben blatt0.pdf

aufgaben: aufgabe1.cpp aufgabe2.cpp aufgabe3.cpp | build
	g++ -o3 -Wall -ffast-math aufgabe1.cpp -o data/aufgabe1
	g++ -o3 -Wall -ffast-math aufgabe2.cpp -o data/aufgabe2
	g++ -o3 -Wall -ffast-math aufgabe3.cpp -o data/aufgabe3

blatt0.pdf: FORCE | build
	  TEXINPUTS=build: \
	  BIBINPUTS=build: \
	  max_print_line=1048576 \
	latexmk \
	  --lualatex \
	  --output-directory=build \
	  --interaction=nonstopmode \
	  --halt-on-error \
	blatt0.tex

code:
	data/aufgabe1
	data/aufgabe2
	data/aufgabe3

build:
	mkdir -p build
	mkdir -p data

clean:
	rm -rf build data

FORCE:

.PHONY: all clean