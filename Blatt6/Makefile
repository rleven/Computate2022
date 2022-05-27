all: data/aufgabe1 data/path0.csv data/path1.csv data/path2.csv data/path3.csv data/path4.csv data/path5.csv data/path6.csv plot main.pdf

data/aufgabe1: aufgabe1.cpp | build
	g++ -O3 -Wall -ffast-math aufgabe1.cpp -o data/aufgabe1

data/path0.csv: aufgabe2.py | build
	python aufgabe2.py

data/path1.csv: aufgabe2.py | build
	python aufgabe2.py

data/path2.csv: aufgabe2.py | build
	python aufgabe2.py

data/path3.csv: aufgabe2.py | build
	python aufgabe2.py

data/path4.csv: aufgabe2.py | build
	python aufgabe2.py

data/path5.csv: aufgabe2.py | build
	python aufgabe2.py

data/path6.csv: aufgabe2.py | build
	python aufgabe2.py

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
	python plots.py

build:
	mkdir -p build
	mkdir -p data
	mkdir -p plots

clean:
	rm -rf build data plots

FORCE:

.PHONY: all clean
