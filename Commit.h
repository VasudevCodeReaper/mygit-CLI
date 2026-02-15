#ifndef COMMIT_H
#define COMMIT_H

#include <string>
#include <filesystem>

class Commit {
public:
    Commit(int id, const std::string& message, const std::string& timestamp);

    void save(const std::filesystem::path& commitPath);

private:
    int id;
    std::string message;
    std::string timestamp;
};

#endif
