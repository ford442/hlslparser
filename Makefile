parser:
	 em++ ./src/*.cpp -o p001.js -sFORCE_FILESYSTEM=1 --pre-js ./src/rSlider.js --pre-js ./src/slideOut.js \
   	-sEXPORTED_FUNCTIONS='["_main","_str"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' -g -Wall -Wformat -Wformat-nonliteral -std=c++11

   

all: parser
	echo 'Built 1ink.us Parser.'
