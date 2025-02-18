//
// Created by Filip Radovic on 9.2.25..
//

#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include <imgui.h>

namespace fs = std::filesystem;

class SearchWindow {
    // Singleton
public:
    SearchWindow(const SearchWindow&) = delete;
    SearchWindow& operator=(const SearchWindow&) = delete;

    // singleton instancing
    static SearchWindow* getInstance();;

    // fonts
    static void setIconFont(ImFont* iconFont);

    // window rendering and search logic
    static void showSearchWindow();

private:
    SearchWindow() = default;

    // rendering
    static void BeginRender();
    static void EndRender();
    static void RenderSearchLogic();
    static void popupWindowSelectable(std::string& selectedFilePath);

    static SearchWindow* instance;
    static ImFont* iconFont;

};



#endif //SEARCHWINDOW_H
