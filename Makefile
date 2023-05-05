parser:
	 emcc ./src/*.cpp -o runr.js -sFORCE_FILESYSTEM=1 --pre-js rSlider.js --pre-js sildeOut.js
   
   

all: parser
	echo 'Built 1ink.us Parser.'
