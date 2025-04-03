//
// Created by Filip Radovic on 22.2.25..
//

#include "../h/ThemePrompt.h"

#include <imgui.h>

#include "../h/IconViewWindow.h"

bool ThemePrompt::themeChosen = false;

void discardPreviousSelection() {
    // Pops all the style variables that were pushed when the previous theme was selected.
    int styleVariableCount = 13;
    for (int i = 0; i < styleVariableCount; i++) ImGui::PopStyleVar();
}

void ThemePrompt::RenderPrompt() {
    // 0 = Dark Theme, 1 = Light Theme.
    static int themeSelection = 0;

    // Begin a window titled "Theme Selector".
    ImGui::Begin("Theme Selector");

    // Radio button for Dark Theme.
    if (ImGui::RadioButton("Forest Dark", themeSelection == 0)){
        themeSelection = 0;
        themeChosen = true;
    }

    // Radio button for Light Theme.
    if (ImGui::RadioButton("Organic Light", themeSelection == 1)){
        discardPreviousSelection();
        themeSelection = 1;
        IconViewWindow::setLightTheme();
        themeChosen = true;
    }

    ImGui::End();
}

bool ThemePrompt::getThemeChosenStatus() {
    return themeChosen;
}


void ThemePrompt::showThemePrompt() {
    RenderPrompt();
}

