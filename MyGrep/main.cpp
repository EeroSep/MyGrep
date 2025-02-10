#include<iostream>
#include<string>
#include<fstream>

void findFromFile(std::string search, std::string fileName, bool showCount, bool lineNo) {

	std::ifstream file;
	std::string line;
	int lineNum = 0, lineCount = 0;

	file.open(fileName);
	if (!file.is_open()) {
		throw std::runtime_error(std::string("Could not open file ") + fileName + "\n");
	}

	while (std::getline(file, line)) {
		lineNum++;
		size_t position = line.find(search);
		if (position != std::string::npos) {
			if (lineNo) {
				std::cout << lineNum << ": ";
			}
			std::cout << line << std::endl;
			lineCount++;
		}
	}
	file.close();

	if (showCount) {
		std::cout << "Total number of lines found: " << lineCount << std::endl;
	}
}

void findInString() {
	std::string longString, search;
	
	std::cout << "Give a string to search from: ";
	if (!std::getline(std::cin, longString) || longString.empty()) {
		throw std::runtime_error("Invalid input");
	}
	std::cout << "Give a search string: ";
	if (!std::getline(std::cin, search) || search.empty()) {
		throw std::runtime_error("Invalid input");
	}
	size_t position = longString.find(search);
	if (position != std::string::npos) {
		std::cout << "'" << search << "' was found in '" << longString << "' in position: " << position << std::endl;
	}
	else {
		std::cout << "'" << search << "' was NOT found in '" << longString << "'\n";
	}
}

int main(int argc, char* argv[]) {

	std::string search, fileName;
	bool lineNo = false, showCount = false;

	try {
		if (argc == 1) {
			findInString();
		}
		else if (argc == 3) {
			search = argv[1];
			fileName = argv[2];
		}
		else if (argc == 4) {
			std::string options = argv[1];
			if (options.substr(0, 2) != "-o") {
				throw std::runtime_error(std::string("Invalid option ") + options + "Use format -o... \n");
			}
			for (char c : options.substr(2)) {
				if (c == 'o') {
					showCount = true;
				}
				else if (c == 'l') {
					lineNo = true;
				}
				else {
					throw std::runtime_error(std::string("Invalid option '") + c + "'\n");
				}
			}


			search = argv[2];
			fileName = argv[3];
		}
		else {
			throw std::runtime_error(std::string("Invalid number of arguments. Usage: ") + argv[0] + (" <search_term> <filename> or no args\n"));
		}

		if (argc == 3 || argc == 4) {
			findFromFile(search, fileName, showCount, lineNo);
		}
		
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n"; 
	}


	return 0;
}
