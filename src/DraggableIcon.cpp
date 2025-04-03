//
// Created by Filip Radovic on 11.2.25..
//

//stb image - texture loading
#define STB_IMAGE_IMPLEMENTATION
#include "../vendor/stb_image/stb_image.h"
#include "../h/DraggableIcon.h"
#include "../h/IconTexturePaths.h"

#include <iostream>
#include <sstream>
#include <imgui.h>
#include <filesystem>

#include "../h/FileTree.h"
#include "../h/IconViewWindow.h"

float DraggableIcon::width = 0, DraggableIcon::height = 0;
int DraggableIcon::statID = 0;
bool DraggableIcon::fileOpened = false;

std::string truncateString(const std::string& str) {
    if (str.length() > 10) {
        return str.substr(0, 10) + "..."; // Take the first 10 characters and append "..."
    }
    return str; // If the string is 10 or fewer characters, return it as is
}


DraggableIcon::DraggableIcon(float x, float y, std::string &name, TreeNode& node) : x(x), y(y), name(name), node(node)  {
    iconId = "button#"  + std::to_string(statID++);
    truncatedName = truncateString(name);
}



void DraggableIcon::setIconSize(float width, float height) {
    DraggableIcon::width = width;
    DraggableIcon::height = height;
}

float DraggableIcon::getWidth() {
    return width;
}

float DraggableIcon::getHeight() {
    return height;
}

void DraggableIcon::LoadTexture(const char *path) {
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

    iconTextureID = textureID;

}


bool DraggableIcon::isFileOpened() {
    return fileOpened;
}

bool DraggableIcon::setFileOpenedStatus(bool status) {
    fileOpened = status;
}

bool DraggableIcon::renderImageButton() {
    bool clicked = false;

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.66f, 0.66f, 0.66f, 0.54f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.42f, 0.42f, 0.42f, 0.67f));

    if (ImGui::ImageButton(iconId.c_str(), iconTextureID, ImVec2(width, height))) {
        clicked = true;
        if (!node.isDirectory()) {
            FileTree::openFile(node.getPathString());
            fileOpened = true;
        }
    }

    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
    ImGui::PopStyleVar();

    return clicked;
}

std::string getFileExtension(const std::string &filename) {
    std::stringstream ss(filename);
    std::string item;
    std::vector<std::string> result;

    // Split by '.'
    while (std::getline(ss, item, '.')) {
        result.push_back(item);
    }

    return result.back();
}

std::string loadTextureBasedOnExtension(const std::string& filename) {
    std::string fileExtension = getFileExtension(filename);

    std::string themePrefix = IconViewWindow::getIconPath();

    std::string iconPath = TEX_FILE;
    if (fileExtension == "rar" || fileExtension == "zip") {
        iconPath = TEX_RAR;
    }
    else if (fileExtension == "exe") {
        iconPath = TEX_EXE;
    }
    else if(fileExtension == "txt") {
        iconPath = TEX_TXT;
    }
    else if(fileExtension == "jpg" || fileExtension == "jpeg" || fileExtension == "png" || fileExtension == "PNG") {
        iconPath = TEX_IMAGE;
    }
    else if (fileExtension == "pdf") {
        iconPath = TEX_PDF;
    }
    else if (fileExtension == "json") {
        iconPath = TEX_JSON;
    }

    return themePrefix + iconPath;
}

void DraggableIcon::loadTextureBasedOnFile(TreeNode &node) {
    std::string iconPath;
    std::string filename = node.getName();

    std::string themePrefix = IconViewWindow::getIconPath();

    try {
        if (node.isDirectory()) iconPath = themePrefix + TEX_FOLDER;
        else if (filename[0] == '.') iconPath = themePrefix + TEX_HIDDEN;
        else iconPath = loadTextureBasedOnExtension(filename);

    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing entry: " << e.what() << std::endl;
    }

    this->LoadTexture(iconPath.c_str());

}

bool DraggableIcon::renderIconWithName(bool render) {
    if(render) {
        ImGui::SetCursorPos(ImVec2(x + width / 4, y + height / 2));

        bool clicked = renderImageButton();


        ImVec2 textPos = ImGui::GetCursorPos();
        textPos.x += x + width / 5;
        ImGui::SetCursorPos(textPos);

        // Render the name below the icon
        ImGui::Text(truncatedName.c_str());
        if (ImGui::IsItemHovered()) {
            // Action when the text is hovered
            ImGui::BeginTooltip();
            ImGui::Text(name.c_str());
            ImGui::EndTooltip();
        }

        return clicked;
    }
    return !render;
}





