#include "Font.h"
#include <fstream>

std::string defaultLetterLines[] = {// it's a ?
	".***.",
	"*...*",
	"...*.",
	"..*..",
	".....",
	"..*.."

};
std::string blankLetterLines[] = {// it's a ?
	".....",
	".....",
	".....",
	".....",
	".....",
	"....."

};

Letter Font::defaultLetter(-1,defaultLetterLines);
Letter Font::blankLetter(32,blankLetterLines);

Letter  Font::constructLetterFromStream(std::istream& input) {
    if (!input.good()) {
        return defaultLetter;
    }

    consumeBlankLines(input);

    char characterName;
    input >> characterName;

    consumeBlankLines(input);

    std::string lines[LETTER_HEIGHT];
    std::string currentLine;
	int lineNum = 0;
    do {
        std::getline(input, currentLine);
        if (currentLine.empty()) {
            break;
        } else {
            lines[lineNum++] = currentLine;
        }
    } while (lineNum<LETTER_HEIGHT);

    return Letter(characterName, lines);
}
void    Font::consumeBlankLines(std::istream& input) {
    while (input.peek() == '\n') {
        input.get();
    }
}
void    Font::constructFontFromStream(std::istream& input) {
	while (input.good()) {
        letters[numOfLetters++] = constructLetterFromStream(input);
    }
}
Letter *Font::getCharacter(char toFind) {
	//special cases
	if(toFind==' ') return &blankLetter;
	//search array
	for(int i=0; i < numOfLetters; i++) {
		if(letters[i].getMatch() == toFind) return &letters[i];
	}
	return &defaultLetter;
}
void    Font::init(const char* fileName) {
	std::ifstream file(fileName);
	init(file);
	file.close();

}
void    Font::init(std::istream& input) {
	constructFontFromStream(input);
}