#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

// Enumeration with three delimiter types
enum Delimiter {
	CR,   // 0
	LF,   // 1
	CRLF  // 2
};

// Override << operator for above enumeration (for std::cout)
std::ostream& operator<<(std::ostream& os, const Delimiter d){
	switch(d) {
		case Delimiter::CR: return os << "<CR>";
		case Delimiter::LF: return os << "<LF>";
		case Delimiter::CRLF: return os << "<CR><LF>";
	}
	return os;
}

// Function determines the delimiter type in a file
// A bit resourceful but it works
Delimiter getDelimiter(std::string path){
	// Count number of lines in file delimited by CR and LF symbols
	std::string line;
	int crLines = 0;
	int lfLines = 0;

	std::ifstream file(path);
	while (std::getline(file, line, '\r')) {
		crLines++;
	}
	file.close();

	std::ifstream file2(path);
	while (std::getline(file2, line, '\n')) {
		lfLines++;
	}
	file2.close();

	// Return delimiter type
	if (crLines > lfLines) return Delimiter::CR;
	if (crLines < lfLines) return Delimiter::LF;
	return Delimiter::CRLF;
}

int main(){
	// Create three test files with different line delimiters - CR(13), LF(10), CRLF
	std::vector<const char*> delimiters = {"\xd", "\xa", "\xd\xa"};
	std::vector<std::string> filePaths = {"cr.txt", "lf.txt", "crlf.txt"};

	for (int i=0; i < 3; i++){
		std::string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
		text = std::regex_replace(text, std::regex(", "), delimiters[i]);
		std::ofstream outfile(filePaths[i]);
		outfile << text;
		outfile.close();
	}
	std::cout << "INFO: Test files with CR, LF, CRLF delimiters are created." << std::endl;

	// Output
	for (int i=0; i < 3; i++){
		std::cout << "INFO: Testing delimiter in file '" << filePaths[i] << "'.";
		Delimiter d = getDelimiter(filePaths[i]);
		std::cout << " Found " << d << std::endl;
	}
	return EXIT_SUCCESS;
}

