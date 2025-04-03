//
// Created by Filip Radovic on 9.2.25..
//

#include "../h/TreeNode.h"
#include <iostream>

TreeNode::TreeNode() : iconInitialized(false), isOpened(false), initialized(false), icon(nullptr), parent(nullptr) {}

TreeNode::TreeNode(const std::filesystem::directory_entry &dirent) : iconInitialized(false), isOpened(false), initialized(false), dirent(dirent), icon(nullptr), parent(nullptr) {}

void TreeNode::initializeIcon() {
    iconInitialized = true;
}

void TreeNode::setIcon(DraggableIcon* icon) {
    this->icon = icon;
    initializeIcon();
}

bool TreeNode::isIconInitialized() const {
    return iconInitialized;
}

DraggableIcon *TreeNode::getIcon() const {
    return icon;
}


void TreeNode::init() {
    if(!initialized){
        try {
            std::filesystem::directory_iterator directoryIterator(dirent, std::filesystem::directory_options::skip_permission_denied);

            for (const auto& dir_entry : directoryIterator) {

                if (dir_entry.path().filename() == ".Trash") continue;

                std::cout << dir_entry.path().string() << std::endl;
                TreeNode child(dir_entry);
                child.parent = this; // possible memory leak
                children.push_back(child);
            }

            initialized = true;
        }
        catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error accessing entry: " << e.what() << std::endl;
        }
    }
}

void TreeNode::open() {
    isOpened = true;
}

void TreeNode::close() {
    isOpened = false;
}

bool TreeNode::isOpen() const {
    return isOpened;
}

void TreeNode::setInitializedStatus(const bool status) {
    initialized = status;
}

bool TreeNode::getInitializedStatus() const {
    return initialized;
}

std::filesystem::directory_entry& TreeNode::getDirectoryEntry() {
    return dirent;
}

void TreeNode::setDirectoryEntry(const fs::directory_entry &dirent) {
    this->dirent = dirent;
}

std::string TreeNode::getPathString() const {
    return dirent.path().string();
}

std::string TreeNode::getName() const {
    return dirent.path().filename().string();
}


std::vector<TreeNode> &TreeNode::getChildren() {
    return children;
}

void TreeNode::addChild(const TreeNode &child) {
    children.push_back(child);
}

bool TreeNode::isDirectory() const {
    return dirent.is_directory();
}

bool TreeNode::direntExists() const {
    return dirent.exists();
}

bool TreeNode::childrenExist() const {
    return !children.empty();
}

TreeNode *TreeNode::getParent() const {
    return parent;
}

bool TreeNode::operator==(const TreeNode &other) const {
    return dirent == other.dirent;
}







