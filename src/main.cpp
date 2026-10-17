#include <cctype>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <optional>

class KeyValueStore
{
public:
    void set(const std::string &key, const std::string &value)
    {
        data_[key] = value;
    }

    std::optional<std::string> get(const std::string &key) const
    {
        auto it = data_.find(key);
        if (it == data_.end())
        {
            return std::nullopt;
        }
        return it->second;
    }

    std::size_t del(const std::string &key)
    {
        return data_.erase(key);
    }

    bool exists(const std::string &key) const
    {
        return data_.count(key) == 1;
    }

private:
    std::unordered_map<std::string, std::string> data_;
};


void handle_set(KeyValueStore &store, std::istringstream &stream)
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
        store.set(key,value);
        std::cout << "OK\n";
    }
}

void handle_get(KeyValueStore &store, std::istringstream &stream)
{
    std::string key;
    stream >> key;

    if (key.empty())
    {
        std::cout << "ERR usage: GET key\n";
    }
    else
    {
        auto value = store.get(key);
        if (!value)
        {
            std::cout << "(nil)\n";
        }
        else
        {
            std::cout << *value << '\n';
        }
    }
}

void handle_del(KeyValueStore &store, std::istringstream &stream) {
    std::string key;
    stream >> key;

    if (key.empty())
    {
        std::cout << "ERR usage: DEL key\n";
    }
    else
    {
        std::cout << store.del(key) << '\n';
    }
}


void handle_exists(KeyValueStore &store, std::istringstream &stream) {
    std::string key;
    stream >> key;

    if (key.empty())
    {
        std::cout << "ERR usage: EXISTS key\n";
    }
    else
    {
        std::cout << store.exists(key) << '\n';
    }
}

int main()
{
    KeyValueStore store;
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