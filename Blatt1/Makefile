all: aufgaben blatt1.pdf

aufgaben: aufgabe1.cpp | build
	g++ -o3 -Wall -ffast-math aufgabe1.cpp -o data/aufgabe1

blatt1.pdf: FORCE | build
	  TEXINPUTS=build: \
	  BIBINPUTS=build: \
	  max_print_line=1048576 \
	latexmk \
	  --lualatex \
	  --output-directory=build \
	  --interaction=nonstopmode \
	  --halt-on-error \
	blatt1.tex

build:
	mkdir -p build
	mkdir -p data

clean:
	rm -rf build data

FORCE:

.PHONY: all clean