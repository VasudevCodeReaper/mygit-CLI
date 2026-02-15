#ifndef REPOSITORY_H
#define REPOSITORY_H

#include<string>

class Repository{
    public:
        void init();
        void add(const std::string& filename);
        void commit(const std::string& message);
        void log();
    
    private:
        bool isInitialized();
        int getLastCommitID();
        void updateHEAD(int id);
        void clearStaging();
        std::string getCurrentTime();
};

#endif
