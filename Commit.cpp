#include "Commit.h"
#include <fstream>

Commit::Commit(int id, const std::string& message, const std::string& timestamp)
    : id(id), message(message), timestamp(timestamp) {}

void Commit::save(const std::filesystem::path& commitPath) {

    std::ofstream metaFile(commitPath / "meta.txt");

    metaFile << "Commit: " << id << "\n";
    metaFile << "Date: " << timestamp;
    metaFile << "Message: " << message << "\n";

    metaFile.close();
}
