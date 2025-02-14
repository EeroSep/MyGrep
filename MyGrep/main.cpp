#include<iostream>
#include<string>
#include<fstream>
#include<stdexcept>
#include<algorithm>
#include<filesystem>
//vaatii c++17 standardin

void findFromFile(const std::string& search, const std::string& fileName, bool occurrences, bool lineNo, bool reverse, bool ignore) {

	std::ifstream file;
	std::string line;
	int lineNum = 0, lineCount = 0;
	std::string tempSearch = search;

	if (!std::filesystem::exists(fileName)) {
		throw std::runtime_error("Could not find file: " + fileName);
	}
	if (std::filesystem::file_size(fileName) == 0) {
		throw std::runtime_error("File is empty: " + fileName);
	}
	file.open(fileName);
	if (!file.is_open()) {
		throw std::runtime_error(std::string("No permissions or file is locked: ") + fileName + "\n");
	}

	if (ignore) {
		std::transform(tempSearch.begin(), tempSearch.end(), tempSearch.begin(), ::tolower);
	}

	while (std::getline(file, line)) {
		lineNum++;
		std::string tempLine = line;
		if (ignore) {
			std::transform(tempLine.begin(), tempLine.end(), tempLine.begin(), ::tolower);
		}
		size_t position = tempLine.find(tempSearch);

		if (reverse) {
			if (position == std::string::npos) {
				if (lineNo) {
					std::cout << lineNum << ": ";
				}
				std::cout << line << std::endl;
				lineCount++;
			}
		}
		else {
			if (position != std::string::npos) {
				if (lineNo) {
					std::cout << lineNum << ": ";
				}
				std::cout << line << std::endl;
				lineCount++;
			}
		}	
	}
	file.close();

	if (occurrences) {
		if (reverse) {
			std::cout << "Total number of lines NOT containing: " << search << " " << lineCount << std::endl;
		}
		else {
			std::cout << "Total number of lines containing: " << search << " " << lineCount << std::endl;
		}
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
	bool lineNo = false, occurrences = false, reverse = false, ignore = false;

	try {
		if (argc == 1) {
			findInString();
		}
		else if (argc == 3) {
			search = argv[1];
			fileName = argv[2];
			findFromFile(search, fileName, occurrences, lineNo, reverse, ignore);
		}
		else if (argc == 4) {
			std::string options = argv[1];
			if (options.substr(0, 2) != "-o") {
				throw std::runtime_error(std::string("Invalid option '") + options + "' Use format -o... \n");
			}
			for (char c : options.substr(2)) {
				if (c == 'o') occurrences = true;
				else if (c == 'l') lineNo = true;
				else if (c == 'r') reverse = true;
				else if (c == 'i') ignore = true;
				else {
					throw std::runtime_error(std::string("Invalid option '") + c + "'\n");
				}
			}

			search = argv[2];
			fileName = argv[3];
			findFromFile(search, fileName, occurrences, lineNo, reverse, ignore);
		}
		else {
			throw std::runtime_error(std::string("Invalid usage of arguments. Do:  -o... <search_term> <filename> or no args\n"));
		}		
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n"; 
		return 1;
	}
	catch (...) { 
        std::cerr << "Unknown exception" << "\n";
	return 1;
    }
	return 0;
}
