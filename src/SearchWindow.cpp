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

                /* Popup window. */

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

void DisplayQueryResults(const std::vector<std::filesystem::path>& filePaths, std::string& selectedFilePath) {

    for (auto& path : filePaths) {
        // Handle user interactions.
        if (ImGui::Selectable(path.string().c_str())) {
            // Store selected file path.
            selectedFilePath = path.string();
            ImGui::OpenPopup("SelectablePopup");
        }
    }

}

void SearchWindow::RenderSearchLogic() {

    static char searchQuery[256] = "";
    static std::vector<fs::path> result;

    // Search bar.
    ImGui::InputText("Filename", searchQuery, IM_ARRAYSIZE(searchQuery));

    // Store path of the user-selected file.
    static std::string selectedFilePath;

    static int oldLen = 0;
    int currLen = strlen(searchQuery);

    // Results of the filemap query.
    static std::vector<std::pair<std::string, std::vector<fs::path>>> cachedResults;


    /* If there is a query, show the previous matching search results. */
    if (currLen > 0) {
        ImGui::Text("Results:");
        if (currLen == oldLen) {
            for (const auto& [file_name, file_path] : cachedResults) {

                /* Display the query results. */
                ImGui::Separator();
                ImGui::Text(ICON_FILE_PLUS "Filename: %s", file_name.c_str());

                DisplayQueryResults(file_path, selectedFilePath);

            }
        }
        /* If there are changes to the query, update the search results. */
        else {
            oldLen = currLen;

            // Clear previous query results.
            cachedResults.clear();

            auto& fileMap = FileTree::getFileMap();
            for (const auto& [filename, paths] : fileMap) {

                if (filename.find(searchQuery) != std::string::npos) {
                    // Update query results.
                    cachedResults.emplace_back(filename, paths);
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


