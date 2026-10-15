#include <iostream>
#include <string>

int main(){
    std::string line;

    while(true) {
        std::cout << "> ";

        if(!std::getline(std::cin, line)) {
            break;
        }

        if (line == "EXIT") {
            break;
        }

        std::cout << line << '\n';
    }
    return 0;
}