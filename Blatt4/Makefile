all: data/aufgabe1 main.pdf

data/aufgabe1: aufgabe1.cpp | build
	g++ -O3 -Wall -ffast-math aufgabe1.cpp -o data/aufgabe1

main.pdf: FORCE | build
	  TEXINPUTS=build: \
	  BIBINPUTS=build: \
	  max_print_line=1048576 \
	latexmk \
	  --lualatex \
	  --output-directory=build \
	  --interaction=nonstopmode \
	  --halt-on-error \
	main.tex

code: data/aufgabe1 | build
	data/aufgabe1

plot: code | build
	python moldyn.py

build:
	mkdir -p build
	mkdir -p data
	mkdir -p plots

clean:
	rm -rf build data plots

FORCE:

.PHONY: all clean
