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
bool FileTree::filesystemIndexed = false;

FileTree *FileTree::getInstance() {
    if (instance == nullptr) {
        instance = new FileTree();
    }
    return instance;
}

void FileTree::setRoot(const TreeNode& root) {
    FileTree::root = root;
}


void FileTree::populateFileMap() {

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
            std::cout << "File Count: " << ++count << std::endl;
        }
        outFile.close();


    }catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing entry: " << e.what() << std::endl;
    }

    // Stop the timer
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the elapsed time
    std::chrono::duration<double> elapsed = end - start;

    filesystemIndexed = true;

    std::cout << "Filesystem indexed: " << elapsed.count() << "s" << std::endl;
}

bool FileTree::getFilesystemIndexStatus() {
    return filesystemIndexed;
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

void FileTree::deleteFile(TreeNode& toDelete) {
    fs::path fileToDelete = toDelete.getPathString();

    try {
        // Check if the file exists
        if (fs::exists(fileToDelete)) {
            // Attempt to delete the file
            if (fs::remove(fileToDelete)) {
                TreeNode* parent = toDelete.getParent();
                auto& siblings = parent->getChildren();

                // Use std::remove to shift the elements that are not equal to nodeToRemove
                auto newEnd = std::remove(siblings.begin(), siblings.end(), toDelete);

                // Erase the "removed" elements from the vector
                siblings.erase(newEnd, siblings.end());

                std::cout << "File deleted successfully.\n";
            } else {
                std::cout << "File could not be deleted.\n";
            }
        } else {
            std::cout << "File does not exist.\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << '\n';
    }
}

TreeNode &FileTree::getRoot() {
    return root;
}

std::unordered_map<std::string, std::vector<std::filesystem::path> > &FileTree::getFileMap() {
    return file_map;
}

