//
// Created by Filip Radovic on 9.2.25..
//

#include <string>
#include <filesystem>
#include <iostream>

#include "../h/SearchWindow.h"

#include "../h/FileTree.h"
#include "../h/IconFont.h"

SearchWindow* SearchWindow::instance = nullptr;
ImFont* SearchWindow::iconFont = nullptr;

SearchWindow *SearchWindow::getInstance() {
    if (instance == nullptr) {
        instance = new SearchWindow();
    }
    return instance;
}

void SearchWindow::BeginRender() {
    ImGui::PushFont(iconFont);
    ImGui::Begin(ICON_SEARCH_WINDOW "Search window", nullptr, ImGuiWindowFlags_NoCollapse);
}

void SearchWindow::EndRender() {
    ImGui::End();
    ImGui::PopFont();
}

void SearchWindow::setIconFont(ImFont *iconFont) {
    SearchWindow::iconFont = iconFont;
}

void SearchWindow::popupWindowSelectable(std::string& selectedFilePath) {
    if (ImGui::BeginPopup("SelectablePopup")) {
        if (!selectedFilePath.empty()) {
            if (ImGui::MenuItem(ICON_PLAY "Run")) {
                FileTree::openFile(selectedFilePath);
                std::cout << "Opening: " << selectedFilePath << std::endl;
                selectedFilePath = "";  // Clear selection after running
            }
        }
        ImGui::EndPopup();
    }
}

void SearchWindow::RenderSearchLogic() {
    static char searchQuery[256] = "";
    static std::vector<fs::path> result;

    // Search bar
    ImGui::InputText("Filename", searchQuery, IM_ARRAYSIZE(searchQuery));

    static std::string selectedFilePath;  // Store selected file

    static int oldLen = 0;
    int currLen = strlen(searchQuery);
    static std::vector<std::pair<std::string, std::vector<fs::path>>> cachedResults;

    if (currLen > 0) {
        ImGui::Text("Results:");
        if (currLen == oldLen) {
            for (const auto& [file_name, file_path] : cachedResults) {
                ImGui::Separator();
                ImGui::Text(ICON_FILE_PLUS "Filename: %s", file_name.c_str());  // Show matching filename
                for (auto& path : file_path) {
                    if (ImGui::Selectable(path.c_str())) {
                        selectedFilePath = path;  // Store selected file
                        ImGui::OpenPopup("SelectablePopup");
                    }
                }
            }
        } else {
            oldLen = currLen;
            cachedResults.clear();
            auto& fileMap = FileTree::getFileMap();
            for (const auto& [filename, paths] : fileMap) {
                if (filename.find(searchQuery) != std::string::npos) {
                    cachedResults.emplace_back(filename, paths);
                    ImGui::Separator();
                    ImGui::Text(ICON_FILE_PLUS "Filename: %s", filename.c_str());  // Show matching filename
                    for (auto& path : paths) {
                        if (ImGui::Selectable(path.c_str())) {
                            selectedFilePath = path;  // Store selected file
                            ImGui::OpenPopup("SelectablePopup");
                        }
                    }
                }
            }
        }
    }


    // Render popup only if a file is selected
    popupWindowSelectable(selectedFilePath);
}


void SearchWindow::showSearchWindow() {
    BeginRender();

    RenderSearchLogic();

    EndRender();
}


