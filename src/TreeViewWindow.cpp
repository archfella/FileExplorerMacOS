//
// Created by Filip Radovic on 9.2.25..
//

#include "../h/IconFont.h"

#include "../h/TreeViewWindow.h"
#include "../h/FileTree.h"

#include <imgui.h>
#include <iostream>
#include <sstream>


TreeViewWindow* TreeViewWindow::instance = nullptr;
ImFont* TreeViewWindow::iconFont = nullptr;

TreeViewWindow *TreeViewWindow::getInstance() {
    if (instance == nullptr) {
        instance = new TreeViewWindow();
    }
    return instance;
}

void TreeViewWindow::BeginRender() {
    ImGui::PushFont(iconFont);
    ImGui::Begin(ICON_ZAP "File Explorer", nullptr, ImGuiWindowFlags_NoCollapse);
}

void TreeViewWindow::EndRender() {
    ImGui::End();
    ImGui::PopFont();
}

void TreeViewWindow::setIconFont(ImFont *iconFont) {
    TreeViewWindow::iconFont = iconFont;
}

std::string TreeViewWindow::getFileExtension(const std::string &filename) {
    std::stringstream ss(filename);
    std::string item;
    std::vector<std::string> result;

    // Split by '.'
    while (std::getline(ss, item, '.')) {
        result.push_back(item);
    }

    return result.back();
}

std::string TreeViewWindow::chooseIconCode(const TreeNode &node) {
    std::string iconCode;
    std::string filename = node.getName();

    try {
        if (node.isDirectory()) iconCode = ICON_FOLDER;
        else if (filename[0] == '.') iconCode = ICON_EYE;
        else iconCode = chooseIconBasedOnExtension(filename);

    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing entry: " << e.what() << std::endl;
    }

    return iconCode;
}

std::string TreeViewWindow::chooseIconBasedOnExtension(const std::string &filename) {
    std::string fileExtension = getFileExtension(filename);

    std::string iconCode;
    if (fileExtension == "rar" || fileExtension == "zip") {
        iconCode = ICON_FILE_PACKAGE;
    }
    else if (fileExtension == "exe") {
        iconCode = ICON_FILE_GRID;
    }
    else if(fileExtension == "txt") {
        iconCode = ICON_FILE_TEXT;
    }
    else if(fileExtension == "jpg" || fileExtension == "jpeg" || fileExtension == "png" || fileExtension == "PNG") {
        iconCode = ICON_FILE_IMAGE;
    }
    else if (fileExtension == "pdf") {
        iconCode = ICON_FILE_BOOK_OPEN;
    }
    else if (fileExtension == "json") {
        iconCode = ICON_FILE_SHOPPING_BAG;
    }

    return iconCode;
}

void TreeViewWindow::popupWindowNode(TreeNode &node) {
    if (ImGui::BeginPopup("TreeNodePopup")) {
        if (ImGui::MenuItem(ICON_PLAY "Run")) {
            FileTree::openFile(node.getPathString());
        }
        if (ImGui::MenuItem(ICON_COPY "Copy")) {
            // copiedNode = node;
            // copy_source_path = node.getPathString();
            FileTree::copyNodeSelection(node);
        }
        if (ImGui::MenuItem(ICON_PASTE "Paste")) {
            //copyFile(node);
            FileTree::copyFile(node);
        }
        if (ImGui::MenuItem(ICON_DELETE "Delete")) {
            //todo
        }
        ImGui::EndPopup();
    }
}

void TreeViewWindow::RenderDescendants(TreeNode &root) {
    // If the root node is opened, do the following:
    if(root.isOpen()){
        for(auto& rootChild : root.getChildren()){ //root.children

            // 1.) Initialize the root children nodes if they are directories, and give them render flags.
            ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_None;
            if(rootChild.isDirectory() && rootChild.direntExists()){
                // If the node is a directory, initialize it - if it doesn't have children, it's a leaf.
                rootChild.init();
                if(!rootChild.childrenExist()) flag |= ImGuiTreeNodeFlags_Leaf;
            }
            else{
                // If the node represents a file, it's a leaf.
                flag |= ImGuiTreeNodeFlags_Leaf;
            }


            // 2.) Render root children and listen for events on those nodes.
            ImGui::PushFont(TreeViewWindow::iconFont);
            std::string iconCode = chooseIconCode(rootChild);
            if(ImGui::TreeNodeEx((iconCode + rootChild.getName()).c_str(), flag)){
                ImGui::PopFont();

                /* Event listeners. */
                if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                    ImGui::OpenPopup("TreeNodePopup");
                    std::cout << "Popup!" << std::endl;
                }
                popupWindowNode(rootChild);

                if(ImGui::IsItemClicked()){
                    rootChild.open();
                }

                if(rootChild.isOpen()){
                    RenderDescendants(rootChild);
                }
                /* --------------- */

                ImGui::TreePop();
            }
            else {
                rootChild.close();
                ImGui::PopFont();
            }
        }
    }
}

void TreeViewWindow::RenderRootNode(TreeNode &root, const std::string &driveName) {
    // Renders the root node with the given driveName, initializes it when clicked, and renders the root children.
    ImGuiTreeNodeFlags flag = ImGuiTreeNodeFlags_None;

    try{
        ImGui::PushFont(TreeViewWindow::iconFont);
        if(ImGui::TreeNodeEx(driveName.c_str(), flag)){
            ImGui::PopFont();

            /* Event listeners. */
            if(ImGui::IsItemClicked()){
                root.open();
                std::cout << root.isOpen() << std::endl;
                if(!root.getInitializedStatus()) {
                    root.init();
                    root.setInitializedStatus(true);
                }
            }
            /* ---------------- */

            if(root.isOpen()) RenderDescendants(root);

            ImGui::TreePop();
        }
        else {
            root.close();
            ImGui::PopFont();
        }
    }
    catch (const std::filesystem::filesystem_error&) {
        ImGui::TreePop();
    }

}

void TreeViewWindow::showTreeViewWindow() {
    BeginRender();

    RenderRootNode(FileTree::getRoot(), "Users");

    EndRender();
}



