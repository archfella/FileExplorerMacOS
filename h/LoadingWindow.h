//
// Created by Filip Radovic on 22.2.25..
//

#ifndef LOADINGWINDOW_H
#define LOADINGWINDOW_H

#include <string>
#include <imgui.h>


class LoadingWindow {
public:
    LoadingWindow(const LoadingWindow&) = delete;
    LoadingWindow& operator=(const LoadingWindow&) = delete;

    // window rendering and search logic
    static void showLoadingWindow();

private:
    LoadingWindow() = default;

    // rendering
    static void RenderLoading();
};



#endif //LOADINGWINDOW_H
