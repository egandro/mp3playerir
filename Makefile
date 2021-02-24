mp3files:
	rm -rf mp3
	mkdir -p mp3
	node mp3.js

clean:
	rm -rf mp3 build

watch:
	minicom -b 9600 -D /dev/ttyACM0

all: mp3files
