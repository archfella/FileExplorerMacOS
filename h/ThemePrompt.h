//
// Created by Filip Radovic on 22.2.25..
//

#ifndef THEMEPROMP_H
#define THEMEPROMP_H


class ThemePrompt {
public:
    ThemePrompt(const ThemePrompt&) = delete;
    ThemePrompt& operator=(const ThemePrompt&) = delete;

    // Window rendering and search logic.
    static void showThemePrompt();
    static bool getThemeChosenStatus();

private:
    ThemePrompt() = default;

    // Rendering.
    static void RenderPrompt();
    static bool themeChosen;

};



#endif //THEMEPROMP_H
