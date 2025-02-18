//
// Created by Filip Radovic on 9.2.25..
//

#ifndef TREEVIEWWINDOW_H
#define TREEVIEWWINDOW_H

#include <imgui.h>
#include "TreeNode.h"

class TreeViewWindow {
    // Singleton
public:
    TreeViewWindow(const TreeViewWindow&) = delete;
    TreeViewWindow& operator=(const TreeViewWindow&) = delete;

    // singleton instancing
    static TreeViewWindow* getInstance();;

    // main window rendering function
    static void showTreeViewWindow();

    // fonts
    static void setIconFont(ImFont* iconFont);

private:
    TreeViewWindow() = default;

    static void RenderDescendants(TreeNode& root);
    static std::string chooseIconBasedOnExtension(const std::string& filename);
    static std::string getFileExtension(const std::string& filename);
    static std::string chooseIconCode(const TreeNode& node);
    static void popupWindowNode(TreeNode& node);

    // rendering
    static void BeginRender();
    static void EndRender();
    static void RenderRootNode(TreeNode& root, const std::string& driveName);

    static TreeViewWindow* instance;
    static ImFont* iconFont;
};


#endif //TREEVIEWWINDOW_H
