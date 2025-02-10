#include<iostream>
#include<string>
#include<fstream>

void findFromFile(std::string search, std::string fileName) {

	std::ifstream file;
	std::string line;

		file.open(fileName);
		if (!file.is_open()) {
			throw std::runtime_error(std::string("Could not open file ") + fileName + "\n");
		}

		while (std::getline(file, line)) {
			size_t position = line.find(search);
			if (position != std::string::npos) {
				std::cout << line << std::endl;
			}
		}
		file.close();
}

void findInString() {
	std::string longString, search;
	try {
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
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
int main(int argc, char* argv[]) {
	try {
		if (argc == 1) {
			findInString();
		}
		else if (argc == 3) {
			findFromFile(argv[1], argv[2]);
		}
		else {
			throw std::runtime_error(std::string("Invalid number of arguments. Usage: ") + argv[0] + (" <search_term> <filename> or no args\n"));
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n"; 
	}


	return 0;
}
