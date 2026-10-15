#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::string line;

    while (true) {
        std::cout << "> ";

        if (!std::getline(std::cin, line)) {
            break;
        }

        std::istringstream stream(line);
        std::string command;
        stream >> command;

        if (command.empty()) {
            continue;
        }

        for (char& c : command) {
            c = std::toupper(static_cast<unsigned char>(c));
        }

        if (command == "EXIT") {
            break;
        }

        std::cout << "Command: " << command << '\n';
    }

    return 0;
}