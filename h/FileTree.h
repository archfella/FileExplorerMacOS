//
// Created by Filip Radovic on 9.2.25..
//

#ifndef TREE_H
#define TREE_H

#include "TreeNode.h"

class FileTree {
    // Singleton
public:
    FileTree(const FileTree&) = delete;
    FileTree& operator=(const FileTree&) = delete;

    // singleton instancing and initialization
    static FileTree* getInstance();
    static void setRoot(const TreeNode& root);

    // filesystem indexing
    static void populateFileMap();

    // file manipulation
    static void copyNodeSelection(const TreeNode& node);
    static void copyFile(TreeNode& dest);
    static void openFile(const std::string& filePath);
    static void deleteFile(const std::string& filePath);

    // getters
    static TreeNode& getRoot();
    static std::unordered_map<std::string, std::vector<std::filesystem::path>>& getFileMap();

private:
    static FileTree* instance;
    FileTree() = default;

    static void writeIndexPopulateMap();
    static void readIndexPopulateMap();

    inline static std::unordered_map<std::string, std::vector<std::filesystem::path>> file_map;
    static TreeNode copiedNode;
    static TreeNode root;
};



#endif //TREE_H
