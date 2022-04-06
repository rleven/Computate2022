all: build/test build/blatt0.pdf

build/test: test.cpp | build
	g++ -o3 -Wall -ffast-math -march=native test.cpp -o build/test

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