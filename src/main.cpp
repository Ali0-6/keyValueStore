#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

void handle_set(std::unordered_map<std::string, std::string> &store,
                std::istringstream &stream)
{
    std::string key;
    std::string value;
    stream >> key >> std::ws;
    std::getline(stream, value);

    if (key.empty() || value.empty())
    {
        std::cout << "ERR usage: SET key value\n";
    }
    else
    {
        store[key] = value;
        std::cout << "OK\n";
    }
}

void handle_get(std::unordered_map<std::string, std::string> &store,
                std::istringstream &stream)
{
    std::string key;
    stream >> key;

    if (key.empty())
    {
        std::cout << "ERR usage: GET key\n";
    }
    else
    {
        auto it = store.find(key);
        if (it == store.end())
        {
            std::cout << "(nil)\n";
        }
        else
        {
            std::cout << it->second << '\n';
        }
    }
}

void handle_del(std::unordered_map<std::string, std::string> &store,
                std::istringstream &stream) {
    std::string key;
    stream >> key;

    if (key.empty())
    {
        std::cout << "ERR usage: DEL key\n";
    }
    else
    {
        std::cout << store.erase(key) << '\n';
    }
}


void handle_exists(std::unordered_map<std::string, std::string> &store,
                std::istringstream &stream) {
    std::string key;
    stream >> key;

    if (key.empty())
    {
        std::cout << "ERR usage: EXISTS key\n";
    }
    else
    {
        std::cout << store.count(key) << '\n';
    }
}

int main()
{
    std::unordered_map<std::string, std::string> store;
    std::string line;

    while (true)
    {
        std::cout << "> ";

        if (!std::getline(std::cin, line))
        {
            break;
        }

        std::istringstream stream(line);
        std::string command;
        stream >> command;

        if (command.empty())
        {
            continue;
        }

        for (char &c : command)
        {
            c = std::toupper(static_cast<unsigned char>(c));
        }

        if (command == "EXIT")
        {
            break;
        }

        if (command == "SET")
        {
            handle_set(store, stream);
        }
        else if (command == "GET")
        {
            handle_get(store,stream);
        }
        else if (command == "DEL")
        {
            handle_del(store,stream);
        }
        else if (command == "EXISTS")
        {
            handle_exists(store,stream);
        }

        else
        {
            std::cout << "ERR unknown command\n";
        }
    }

    return 0;
}