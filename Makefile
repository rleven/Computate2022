all: test build/blatt0.pdf

test: test.cpp
	g++ -Wall -ffast-math -march=native test.cpp -o test

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
	rm -f test
	rm -rf build

FORCE:

.PHONY: all clean