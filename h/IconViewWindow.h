//
// Created by Filip Radovic on 11.2.25..
//

#ifndef ICONVIEWWINDOW_H
#define ICONVIEWWINDOW_H
#include <imgui.h>
#include <stack>

#include "TreeNode.h"


class IconViewWindow {
    // Singleton
public:
    IconViewWindow(const IconViewWindow&) = delete;
    IconViewWindow& operator=(const IconViewWindow&) = delete;

    static void showIconViewWindow();

private:
    IconViewWindow() = default;

    // rendering
    static void BeginRender();
    static void EndRender();
    static void Render();
    static void RenderChildrenIcons();
    static void RenderBackButton();

    static ImFont* iconFont;
    static std::stack<TreeNode*> nodeStack;
    static bool goBack;
};



#endif //ICONVIEWWINDOW_H
