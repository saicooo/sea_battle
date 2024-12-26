#include <iostream>
#include <fstream>
#include <unordered_map>

class TerminalInputHandler {
public:
    TerminalInputHandler() {
        // Загрузка соответствия команд из файла
        loadCommands("commands.txt");
    }

    char getKey() {
        char key;
        std::cin >> key;
        return key;
    }

private:
    void loadCommands(const std::string& filename) {
        std::ifstream file(filename);
        if (!file) {
            // Если невозможно считать из файла, задаем команды по умолчанию
            commands['s'] = "save";
            commands['l'] = "load";
            commands['n'] = "new";
            commands['r'] = "run";
            return;
        }

        char key;
        std::string command;
        while (file >> key >> command) {
            commands[key] = command;
        }
    }

    std::unordered_map<char, std::string> commands;
};