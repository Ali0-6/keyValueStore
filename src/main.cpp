#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

int main() {
    std::unordered_map<std::string, std::string> store;
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

        if (command == "SET") {
            std::string key;
            std::string value;
            stream >> key >> std::ws;
            std::getline(stream, value);
            store[key] = value;
            std::cout << "OK\n";
        } else if (command == "GET") {
            std::string key;
            stream >> key;
            auto it = store.find(key);
            if (it == store.end()) {
                std::cout << "(nil)\n";
            } else {
                std::cout << it->second << '\n';
            }
        } else {
            std::cout << "ERR unknown command\n";
        }
    }

    return 0;
}