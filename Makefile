parser:
	 emcc ./src/*.cpp -o runr.js -sFORCE_FILESYSTEM=1 --pre-js ./src/rSlider.js --pre-js ./src/sildeOut.js
   
   

all: parser
	echo 'Built 1ink.us Parser.'
