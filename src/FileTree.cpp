//
// Created by Filip Radovic on 9.2.25..
//

#include "../h/FileTree.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <imgui.h>

TreeNode FileTree::root;
FileTree* FileTree::instance = nullptr;
TreeNode FileTree::copiedNode;

FileTree *FileTree::getInstance() {
    if (instance == nullptr) {
        instance = new FileTree();
    }
    return instance;
}

void FileTree::setRoot(const TreeNode& root) {
    FileTree::root = root;
}


void FileTree::writeIndexPopulateMap() {
    auto start = std::chrono::high_resolution_clock::now();

    try {
        std::ofstream outFile("index.txt");

        // Check if the file opened successfully
        if (!outFile) {
            std::cerr << "Error opening file for writing." << std::endl;
        }

        std::filesystem::directory_entry start_dir("/Users");
        std::cout << start_dir.path() << std::endl;
        long long count = 0;
        for (const auto& entry : std::filesystem::recursive_directory_iterator(start_dir)) {

            // For MacOS
            //if (entry.path().filename() == ".Trash") continue;

            //if (entry.is_regular_file()) {
            // Insert the filename as the key and the path as the value

            file_map[entry.path().filename().string()].push_back(entry.path());
            outFile << entry.path().filename().string() << "," << entry.path() << "\n";
            //outFile.flush();
            //}
            std::cout << "Count: " << ++count << std::endl;
        }
        outFile.close();

        /*Signal that the filesystem cashing is complete.*/
        static std::ofstream indexed("indexed.txt");
        indexed << count << std::endl;
        indexed.close();

    }catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing entry: " << e.what() << std::endl;
    }

    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Filesystem indexed: " << elapsed.count() << "s" << std::endl;
}

void FileTree::readIndexPopulateMap() {

    std::ifstream indexInput("index.txt");
    if (!indexInput) {
        std::cerr << "Failed to open index.txt" << std::endl;
        exit(1);
    }

    long long count = 0;
    std::string line;
    while (std::getline(indexInput, line)) {
        std::istringstream lineStream(line); // Create a stringstream for splitting
        std::string key, value;

        // Split the line by the delimiter ','
        if (std::getline(lineStream, key, ',') && std::getline(lineStream, value, ',')) {
            auto start = std::chrono::high_resolution_clock::now();
            file_map[key].emplace_back(value); // Insert the key-value pair into the hash map
            count++;
            std::cout << count << std::endl;
            auto end = std::chrono::high_resolution_clock::now();

            // Calculate the elapsed time
            std::chrono::duration<double> elapsed = end - start;

            std::cout << "Hashmap accessed: " << elapsed.count() << "s" << std::endl;
        } else {
            std::cerr << "Skipping malformed line: " << line << std::endl;
        }
    }



    indexInput.close();
}

void FileTree::populateFileMap() {
    std::ifstream indexed("indexed.txt");
    if(!indexed){
        writeIndexPopulateMap();

        std::ofstream createFile("indexed.txt");
        if(!createFile) {
            std::cerr << "Error creating an indexed.txt file!" << std::endl;
        }

    }else{
        readIndexPopulateMap();
        std::cout << "Map populated!" << std::endl;
    }
}

void FileTree::copyNodeSelection(const TreeNode& node) {
    copiedNode = node;
}

void FileTree::copyFile(TreeNode &dest) {
    std::string destination_directory = dest.getPathString();

    // Append the file name from the source path to construct the full destination path
    std::string copy_source_path = copiedNode.getPathString();
    std::string paste_destination_path = destination_directory + "/" + std::filesystem::path(copy_source_path).filename().string();

    copiedNode.setDirectoryEntry(std::filesystem::directory_entry(paste_destination_path));

    dest.addChild(copiedNode);

    try
    {
        std::filesystem::copy(copy_source_path, paste_destination_path);
        std::cout << "File copied!" << std::endl;
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        ImGui::Text("Error copying file: %s", e.what());
    }
}

void FileTree::openFile(const std::string &filePath) {
    std::string command = "open \"" + filePath + "\"";
    system(command.c_str());
}

void FileTree::deleteFile(const std::string &filePath) {
    // todo
}

TreeNode &FileTree::getRoot() {
    return root;
}

std::unordered_map<std::string, std::vector<std::filesystem::path> > &FileTree::getFileMap() {
    return file_map;
}

