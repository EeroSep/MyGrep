#include<iostream>
#include<string>

int main() {
	std::string longString, search;
	try {
		std::cout << "Give a string to search from: ";
		if (!std::getline(std::cin, longString) || search.empty()) {
			throw std::runtime_error("Invalid input");
		}

		std::cout << "Give a search string: ";
		if (!std::getline(std::cin, search) || search.empty()) {
			throw std::runtime_error("Invalid input");
		}

		size_t position = longString.find(search);

		if (position != std::string::npos){
			std::cout << "'" << search << "' was found in '" << longString << "' in position: " << position << std::endl;
		}
		else {
			std::cout << "'" << search << "' was NOT found in '" << longString << "'\n";
		}


	}
	catch (const std::exception& e) {
		std::cerr << "Exception: " << e.what() << "\n";
			return 1;
	}
	catch (...){
		std::cerr << "Unexpected exception \n";
		return 1;
	}
	return 0;
}