//
// Created by Filip Radovic on 11.2.25..
//

#ifndef DRAGGABLEICON_H
#define DRAGGABLEICON_H

#include <string>
#include <GL/glew.h>
#include "TreeNode.h"

class DraggableIcon {
public:
    DraggableIcon(float x, float y, std::string& name, TreeNode& node);

    void LoadTexture(const char* path);
    void loadTextureBasedOnFile(TreeNode& node);
    static void setIconSize(float width, float height);
    static float getWidth();
    static float getHeight();
    bool renderIconWithName(bool render);
    static bool isFileOpened();
    static void setFileOpenedStatus(bool status);

private:
    bool renderImageButton();
    static bool fileOpened;

    static int statID;
    std::string iconId;
    float x, y;
    std::string name, truncatedName;
    static float width, height;
    GLuint iconTextureID;
    TreeNode& node;
};



#endif //DRAGGABLEICON_H
