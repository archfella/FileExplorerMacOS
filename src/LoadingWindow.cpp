//
// Created by Filip Radovic on 22.2.25..
//

#include "../h/LoadingWindow.h"

#include "../h/FileTree.h"


void DrawSpinner(float radius, int segments) {
    // Get the display size from ImGui's IO object.
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 displaySize = io.DisplaySize;

    // Create a full-screen window with no decorations or background.
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(displaySize);
    ImGui::Begin("Loading Screen", nullptr,
                 ImGuiWindowFlags_NoTitleBar |
                 ImGuiWindowFlags_NoScrollbar |
                 ImGuiWindowFlags_NoScrollWithMouse );

    // Compute the center of the screen.
    ImVec2 center(displaySize.x * 0.5f, displaySize.y * 0.5f);

    // Retrieve the draw list for custom drawing.
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // Get the current time to create a rotation effect.
    float time = ImGui::GetTime();
    float speed = 3.0f; // Adjust rotation speed as desired

    // Draw each segment of the spinner with a time-dependent rotation.
    for (int i = 0; i < segments; i++) {
        // Base angle plus time-based offset for continuous rotation.
        float angle = (static_cast<float>(i) / segments) * 2.0f * 3.14159265359f + time * speed;

        // Create a fading effect across segments.
        float alpha = 1.0f - (static_cast<float>(i) / segments);
        if (alpha < 0.1f)
            alpha = 0.1f;

        // Calculate start and end points for the line segment.
        ImVec2 start(center.x + cos(angle) * radius, center.y + sin(angle) * radius);
        ImVec2 end(center.x + cos(angle) * (radius * 0.6f), center.y + sin(angle) * (radius * 0.6f));

        // Draw the spinner line.
        draw_list->AddLine(start, end, IM_COL32(255, 255, 255, static_cast<int>(alpha * 255)), 4.0f);
    }

    // Draw a loading text below the spinner.
    const char* loadingText = "Indexing the filesystem for fast searches...";
    ImVec2 textSize = ImGui::CalcTextSize(loadingText);
    draw_list->AddText(ImVec2(center.x - textSize.x * 0.5f, center.y + radius + 10.0f),
                       IM_COL32(255, 255, 255, 255), loadingText);

    ImGui::End();
}

void LoadingWindow::RenderLoading() {
    if (FileTree::getFilesystemIndexStatus()) return; // Stop showing if loading is done

    DrawSpinner(20.0f, 12);
}

void LoadingWindow::showLoadingWindow() {
    RenderLoading();
}


