#include <fstream>
#include <stdexcept>

class GameSaver {
public:
    GameSaver(const std::string& filename, std::ios::openmode mode) : file(filename, mode) {
        if (!file) {
            throw std::runtime_error("Failed to open file.");
        }
    }

    ~GameSaver() {
        file.close();
    }

    std::ofstream& getOutputStream() {
        return file;
    }

    std::ifstream& getInputStream() {
        return file;
    }

private:
    std::fstream file;
};