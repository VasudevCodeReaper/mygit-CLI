#include "Repository.h"
#include "Commit.h"
#include <iostream>
int main(int argc, char* argv[]) {

    Repository repo;

    if (argc < 2) {
        std::cout << "Usage: mygit <command>\n";
        return 1;
    }

    std::string command = argv[1];

    if (command == "init") {
        repo.init();
    }
    else if (command == "add" && argc >= 3) {
        repo.add(argv[2]);
    }
    else if (command == "commit" && argc >= 3) {
        repo.commit(argv[2]);
    }
    else if (command == "log") {
        repo.log();
    }
    else {
        std::cout << "Invalid command.\n";
    }

    return 0;
}
