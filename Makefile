parser:
	 em++ ./src/*.cpp -o p001.js -I./src/*.h -sFORCE_FILESYSTEM=1 --pre-js ./src/rSlider.js --pre-js ./src/slideOut.js \
   	-sTEXTDECODER=0 -sEXPORTED_FUNCTIONS='["_main","_str"]' -sEXPORTED_RUNTIME_METHODS='["ccall"]' -g -Wall -Wformat -Wformat-nonliteral -std=c++20 -stdlib=libc++

   

all: parser
	echo 'Built 1ink.us Parser.'
