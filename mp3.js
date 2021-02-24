const { execSync } = require("child_process");
const fs = require('fs');

const arr=[
	"Power",
	"Stop",
	"Increase Volume",
	"Fast Back",
	"Pause",
	"Fast Forward",
	"Down",
	"Decrease Volume",
	"Up",
	"Equalizer",
	"Station / Repeat",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
];


fs.appendFileSync("mp3/card_content.h", "#ifndef __CARD_CONTENT_H\n");
fs.appendFileSync("mp3/card_content.h", "#define __CARD_CONTENT_H\n");
fs.appendFileSync("mp3/card_content.h", "\n");


for(let i=0; i < arr.length; i++) {
	const text = arr[i];
	const prefix=pad(i, 4);
	const outFile=prefix + ".mp3";
	console.log(text);
	console.log(outFile);

	let data = outFile + ": \"" + text + "\"\n";
	fs.appendFileSync("mp3/index.txt", data);

	data = "#define MP3_ID_" + prefix + " " + i + " // \"" + text + "\"\n";
	fs.appendFileSync("mp3/card_content.h", data);

	createMP3(i, text, outFile);
}


fs.appendFileSync("mp3/card_content.h", "\n");
fs.appendFileSync("mp3/card_content.h", "#endif //__CARD_CONTENT_H\n");

function createMP3(i, text, outFile) {
	//execSync("pico2wave -l=de-DE -w=/tmp/test" + i + ".wav \"" + text + "\"");
	execSync("pico2wave -w=/tmp/test" + i + ".wav \"" + text + "\"");
	execSync("ffmpeg -i /tmp/test" + i + ".wav -acodec mp3 mp3/" + outFile);
	execSync("rm -f /tmp/test" + i + ".wav");
}

function pad(num, size) {
    var s = "000000000" + num;
    return s.substr(s.length-size);
}
