//
// Created by Filip Radovic on 9.2.25..
//

#ifndef TREENODE_H
#define TREENODE_H

#include <filesystem>

class DraggableIcon;

namespace fs = std::filesystem;

class TreeNode {
public:
    TreeNode();
    ~TreeNode();
    explicit TreeNode(const std::filesystem::directory_entry& dirent);

    /*Initializes the TreeNode structure.*/
    void init();

    // getters/setters
    void open();
    void close();
    bool isOpen() const;
    void setInitializedStatus(const bool status);
    bool getInitializedStatus() const;
    fs::directory_entry& getDirectoryEntry();
    void setDirectoryEntry(const fs::directory_entry& dirent);
    std::string getPathString() const;
    std::string getName() const;
    std::vector<TreeNode>& getChildren();
    void initializeIcon();
    bool isIconInitialized();
    void setIcon(DraggableIcon* icon);
    DraggableIcon* getIcon();

    // other
    void addChild(const TreeNode& child);
    bool isDirectory() const;
    bool direntExists() const;
    bool childrenExist() const;

private:
    bool iconInitialized;
    bool isOpened;
    bool initialized;
    std::vector<TreeNode> children;
    fs::directory_entry dirent;
    DraggableIcon* icon;
};



#endif //TREENODE_H
