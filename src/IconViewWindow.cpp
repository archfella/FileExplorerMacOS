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
std::string IconViewWindow::iconPath;
bool IconViewWindow::lightTheme = true;
std::string IconViewWindow::currentPath = "/Users/";
std::vector<std::string> IconViewWindow::prevPaths;

void IconViewWindow::BeginRender() {
    ImGui::PushFont(iconFont);
    ImGui::Begin(ICON_ZAP "Icon View", nullptr, ImGuiWindowFlags_NoCollapse);
}

void IconViewWindow::EndRender() {
    ImGui::End();
    ImGui::PopFont();
}

void IconViewWindow::setDarkTheme() {
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg]               = ImVec4(0.20f, 0.22f, 0.20f, 0.94f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.20f, 0.22f, 0.20f, 0.94f);
    colors[ImGuiCol_PopupBg]                = ImVec4(0.20f, 0.22f, 0.20f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.72f, 0.72f, 0.72f, 0.50f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.54f);
    colors[ImGuiCol_CheckMark]              = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.56f, 0.56f, 0.56f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.25f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.42f, 0.50f, 0.45f, 1.00f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.34f, 0.34f, 0.34f, 0.80f);
    colors[ImGuiCol_Tab]                    = ImVec4(0.16f, 0.16f, 0.16f, 0.86f);
    colors[ImGuiCol_TabSelected]            = ImVec4(0.36f, 0.36f, 0.36f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.03f, 0.03f, 0.03f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.21f, 0.21f, 0.21f, 1.00f);



    // Frame
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(11, 5));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(16, 7));
    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 18);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 14);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
    ImGui::PushStyleVar(ImGuiStyleVar_TabBorderSize, 1);

    // Rounding
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);
    ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 10);
    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 2);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 5);
    ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 4);

    iconPath = "../textures/icons/white/";
    lightTheme = false;
}

void IconViewWindow::setLightTheme() {
    // Colors
    ImVec4* colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_Text]                   = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    colors[ImGuiCol_WindowBg]               = ImVec4(0.96f, 0.95f, 0.95f, 0.94f);
    colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_PopupBg]                = ImVec4(1.00f, 1.00f, 1.00f, 0.94f);
    colors[ImGuiCol_Border]                 = ImVec4(0.00f, 0.00f, 0.00f, 0.50f);
    colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg]                = ImVec4(0.66f, 0.66f, 0.66f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.42f, 0.42f, 0.42f, 0.67f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.54f, 0.54f, 0.54f, 0.67f);
    colors[ImGuiCol_TitleBg]                = ImVec4(0.51f, 0.62f, 0.55f, 1.00f);
    colors[ImGuiCol_TitleBgActive]          = ImVec4(0.41f, 0.51f, 0.44f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
    colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.51f, 0.62f, 0.55f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.44f, 0.52f, 0.47f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
    colors[ImGuiCol_CheckMark]              = ImVec4(0.46f, 0.78f, 0.46f, 1.00f);
    colors[ImGuiCol_SliderGrab]             = ImVec4(0.46f, 0.46f, 0.46f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.f, 0.f, 0.f, 1.00f);
    colors[ImGuiCol_Button]                 = ImVec4(0.51f, 0.62f, 0.55f, 1.00f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.42f, 0.50f, 0.45f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.42f, 0.51f, 0.45f, 1.00f);
    colors[ImGuiCol_Header]                 = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.51f, 0.62f, 0.55f, 0.80f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.46f, 0.78f, 0.46f, 1.00f);
    colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    colors[ImGuiCol_SeparatorActive]        = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
    colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
    colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
    colors[ImGuiCol_Tab]                    = ImVec4(1.00f, 1.00f, 1.00f, 0.86f);
    colors[ImGuiCol_TabSelected]            = ImVec4(0.75f, 0.75f, 0.75f, 1.00f);
    colors[ImGuiCol_TabSelectedOverline]    = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_TabDimmed]              = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
    colors[ImGuiCol_TabDimmedSelected]      = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
    colors[ImGuiCol_TabDimmedSelectedOverline]  = ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
    colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
    colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
    colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
    colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
    colors[ImGuiCol_TableBorderLight]       = ImVec4(0.23f, 0.23f, 0.25f, 1.00f);
    colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
    colors[ImGuiCol_TextLink]               = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
    colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    colors[ImGuiCol_NavCursor]              = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);


    // Frame
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(11, 5));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(16, 7));
    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 18);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 14);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
    ImGui::PushStyleVar(ImGuiStyleVar_TabBorderSize, 1);

    // Rounding
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 10);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10);
    ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 10);
    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 2);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 5);
    ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 4);

    iconPath = "../textures/icons/black/";
    lightTheme = true;
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
        std::string backPath = iconPath + "back.png";
        texId = LoadTexture(backPath.c_str());
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

void IconViewWindow::displayCurrentPath() {
    ImGui::SetCursorPos(ImVec2(65, 37));
    ImGui::Text(currentPath.c_str());
}


void IconViewWindow::RenderChildrenIcons() {

    if (goBack) {
        currentPath = prevPaths.back();
        prevPaths.pop_back();
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
            auto childIcon = new DraggableIcon(x, y, fullName, child);
            childIcon->loadTextureBasedOnFile(child);
            child.setIcon(childIcon);
        }

        childIconClicked = child.getIcon()->renderIconWithName(!childIconClicked);
        if (DraggableIcon::isFileOpened()) {
            DraggableIcon::setFileOpenedStatus(false);
            childIconClicked = false;
        }

        if (childIconClicked) {
            nodeStack.push(&child);
            childIconClicked = false;
            prevPaths.push_back(parent->getPathString());
            currentPath = child.getPathString();
            RenderChildrenIcons();
        }

        ImVec2 windowSize = ImGui::GetWindowSize();
        x += DraggableIcon::getWidth() * 2;
        if (x >= windowSize.x - DraggableIcon::getWidth()) {
            x = 0;
            y += DraggableIcon::getHeight() * 2;
        }

    }
}

void IconViewWindow::initRootIcon(TreeNode& root) {
    // initialize the icon class
    DraggableIcon::setIconSize(80, 80);

    std::string rootName = "Users";
    auto rootIcon = new DraggableIcon(0 ,30, rootName, root);
    std::string folderIconPath = iconPath + "folder.png";
    rootIcon->LoadTexture(folderIconPath.c_str());
    root.setIcon(rootIcon);
}

std::string &IconViewWindow::getIconPath() {
    return iconPath;
}


void IconViewWindow::Render() {

    TreeNode& root = FileTree::getRoot();

    static bool clicked = false;

    displayCurrentPath();

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




