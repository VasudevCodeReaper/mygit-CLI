#include "Repository.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include "Commit.h"

namespace fs = std::filesystem;

void Repository::init(){
    // return if it exists
    if(fs::exists(".mygit")){
        std::cout<<"Repository already initialized.\n";
        return;
    }
    // create one if not there
    fs::create_directories(".mygit");
    fs::create_directories(".mygit/commits");
    fs::create_directories(".mygit/staging");
    // create Head file which is initialized to 0
    std::ofstream headFile(".mygit/HEAD");
    headFile<<0;
    headFile.close();

    std::cout<<"initialized empty MINIGIT repo.\n";

}

bool Repository::isInitialized(){
    return fs::exists(".mygit");
}

void Repository::add(const std::string& filename){
    if(!isInitialized()){
        std::cout<<"REPO IS NOT INITIALIZED.\n";
        return;
    }

    if(!fs::exists(filename)){
        std::cout<<"FILE DOES NOT EXIST.\n";
        return;
    }

    fs::path sourcePath(filename);
    fs::path destinationPath = fs::path(".mygit/staging")/sourcePath.filename();

    fs::copy_file(
        sourcePath,
        destinationPath,
        fs::copy_options::overwrite_existing
    );

    std::cout<<"ADDED" << sourcePath.filename()<<" TO STAGING.\n";

}

int Repository::getLastCommitID(){

    std::ifstream headFile(".mygit/HEAD");
    if (!fs::exists(".mygit/commits") || fs::is_empty(".mygit/commits")) {
        return 0;
    }
    int id = 0;

    if(headFile){
        headFile>>id;
    }
    headFile.close();
    return id;
}

void Repository::updateHEAD(int id){
    std::ofstream headFile(".mygit/HEAD");
    headFile<<id;
    headFile.close();
}

void Repository::clearStaging(){
    for(const auto& entry : fs::directory_iterator(".mygit/staging")){
        fs::remove(entry.path());
    }
}

std::string Repository::getCurrentTime(){
    auto now = std::chrono::system_clock::now();
    std::time_t timeNow = std::chrono::system_clock::to_time_t(now);

    return std::ctime(&timeNow);
}

void Repository::commit(const std::string& message){
    if(!isInitialized()){
        std::cout<<"Repository not initialized.\n";
        return;
    }
    if(fs::is_empty(".mygit/staging")){
        std::cout<<"nothing to commit.\n";
        return;
    }
    int lastID = getLastCommitID();
    int newID = lastID + 1;

    fs::path commitPath = fs::path(".mygit/commits")/std::to_string(newID);
    fs::create_directories(commitPath);

    for(const auto& entry : fs::directory_iterator(".mygit/staging")){
        fs::copy_file(
            entry.path(),
            commitPath/entry.path().filename(),
            fs::copy_options::overwrite_existing
        );
    }
    Commit commit(newID, message, getCurrentTime());
    commit.save(commitPath);

    updateHEAD(newID);
    clearStaging();

    std::cout<< "Committed as "<< newID << ".\n";
}

void Repository::log(){
    if(!isInitialized()){
        std::cout << "Repository not initialized.\n";
        return;
    }

    int latest = getLastCommitID();
    if(latest == 0){
        std::cout << "No commits yet.\n";
        return;
    }

    for(int i = latest;i>=1;i--){
        fs::path metaPath = fs::path(".mygit/commits")/std::to_string(i)/"meta.txt";
        if(fs::exists(metaPath)){
            std::ifstream metaFile(metaPath);
            std::string line;

            while(std::getline(metaFile,line)){
                std::cout<<line<<"\n";
            }
            metaFile.close();

            std::cout<<"---------------------------\n";
        }
    }
}