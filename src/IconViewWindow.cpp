//
// Created by Filip Radovic on 11.2.25..
//

#include "../h/IconViewWindow.h"
#include "../h/DraggableIcon.h"
#include "../h/FileTree.h"
#include "../h/IconFont.h"
#include "../vendor/stb_image/stb_image.h"

#include <iostream>
#include <sstream>



ImFont* IconViewWindow::iconFont = nullptr;
std::stack<TreeNode*> IconViewWindow::nodeStack;
bool IconViewWindow::goBack = false;

void IconViewWindow::BeginRender() {
    ImGui::PushFont(iconFont);
    ImGui::Begin(ICON_ZAP "Icon View", nullptr, ImGuiWindowFlags_NoCollapse);
}

void IconViewWindow::EndRender() {
    ImGui::End();
    ImGui::PopFont();
}

GLuint LoadTexture(const char *path) {
    int width, height, channels;
    unsigned char* data = stbi_load(path, &width, &height, &channels, 4);

    if (!data) {
        std::cerr << "Failed to load texture: " << path << std::endl;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);

    return textureID;

}

void IconViewWindow::RenderBackButton() {
    static GLuint texId = -1;
    static bool initialized = false;
    if (!initialized) {
        texId = LoadTexture("../textures/icons/back.png");
        initialized = true;
    }

    // Use PushID to create a unique ID for the button
    ImGui::PushID("back_button");

    ImGui::SetCursorPos(ImVec2(20, 30));

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.42f, 0.42f, 0.42f, 0.67f));
    // Create the ImageButton with a fixed ID, texId, and size
    if (ImGui::ImageButton("back_button", texId, ImVec2(30, 30))) {
        goBack = true;
    }
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();

    // Pop the ID after the button is created
    ImGui::PopID();
}

void IconViewWindow::RenderChildrenIcons() {

    if (goBack) {
        goBack = false;
        nodeStack.pop();
        if (nodeStack.empty()) return;
    }
    TreeNode* parent = nodeStack.top();

    static bool childIconClicked = false;

    // TreeNode initialization
    if(!parent->getInitializedStatus()) {
        parent->init();
        parent->setInitializedStatus(true);
    }

    auto& children = parent->getChildren();
    float x = 0, y = 30;


    for (auto& child : children) {
        std::string fullName = child.getName();

        if (!child.isIconInitialized()) {
            auto childIcon = new DraggableIcon(x, y, fullName);
            childIcon->loadTextureBasedOnFile(child);
            child.setIcon(childIcon);
        }

        childIconClicked = child.getIcon()->renderIconWithName(!childIconClicked);

        if (childIconClicked) {
            nodeStack.push(&child);
            childIconClicked = false;
            RenderChildrenIcons();
        }

        ImVec2 windowSize = ImGui::GetWindowSize();
        x += DraggableIcon::getWidth() * 2;
        if (x >= windowSize.x - DraggableIcon::getWidth() / 2) {
            x = 0;
            y += DraggableIcon::getHeight() * 2;
        }

    }
}

void initRootIcon(TreeNode& root) {
    // initialize the icon class
    DraggableIcon::setIconSize(80, 80);

    std::string rootName = "Users";
    auto rootIcon = new DraggableIcon(0 ,30, rootName);
    rootIcon->LoadTexture("../textures/icons/folder.png");
    root.setIcon(rootIcon);
}


void IconViewWindow::Render() {

    TreeNode& root = FileTree::getRoot();

    static bool clicked = false;

    if (!root.isIconInitialized()) initRootIcon(root);

    if (nodeStack.empty()) clicked = root.getIcon()->renderIconWithName(!clicked);
    else RenderChildrenIcons();

    if (clicked) {
        nodeStack.push(&root);
        clicked = false;
    };
}

void IconViewWindow::showIconViewWindow() {
    BeginRender();
    Render();
    RenderBackButton();
    EndRender();
}




