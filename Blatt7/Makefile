all: data/aufgabe1 data/aufgabe2 main.pdf

data/aufgabe1: aufgabe1.py | build
	python aufgabe1.py

data/aufgabe2: aufgabe2.cpp | build
	g++ -O3 -Wall -ffast-math aufgabe2.cpp -o data/aufgabe2

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

code: data/aufgabe2 | build
	data/aufgabe2

plot: code | build
	python plots.py

build:
	mkdir -p build
	mkdir -p data
	mkdir -p plots

clean:
	rm -rf build data plots

FORCE:

.PHONY: all clean
