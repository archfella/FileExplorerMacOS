# Cross-Platform File Explorer 

## Description

* Cross-Platform File Explorer app developed using ImGui and OpenGL in C++.
In the current moment app works only on **macOS**, but will soon be available for both Windows (see README_Windows.md) and Linux.

---

## Table of Contents

1. [Features](#features)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Updates](#updates)
5. [License](#license)
6. [Sources](#sources)

---

## Features

* Tree-view of the filesystem.
* Icon-view of the filesystem.
* Fast filename searching with filesystem caching.
* Basic file manipulation (copy, paste, run/open, delete).
---

## Installation

### macOS

#### Prerequisites:
Before building the project, ensure you have the following installed:

* **CMake** (version 3.10 or later)
* A **C++ Compiler** supporting C++17
* **GLFW**:

On macOS, you can install GLFW using Homebrew:
  ```bash
  brew install glfw
  ```

* **GLEW**:

Install GLEW using Homebrew:
  ``` bash
  brew install glew
  ```

* **OpenGL**:

macOS provides OpenGL as part of its system libraries, so no additional installation is needed.

* **ImGui**:

The ImGui library is included in the project under the vendor/ImGui directory, so no extra installation is needed for it.

---

## Usage

### GUI

![GUI](readme_images/all.png)

* GUI consists of three windows:
  1. **Tree View** (leftmost window)
  2. **Icon View** (bottom right window)
  3. **Search window** (top right window)


* The different windows are fully resizable, movable and support simultaneous interaction.

### Tree View GUI

Here is a closer view of the Tree GUI:

![Tree](readme_images/tree.png)

* Subdirectories and files of a directory can be viewed by clicking on the directory
icon:

![Collapse](readme_images/collapse.png)

* Right-click on the file icon, the file manipulation window will pop up, then choose
the option that you want. 
* 'Run' option opens the file in the default program.
  * Note: 'Delete' option will be available in some of the future commits.

![Run](readme_images/run.png)

* Example:

![text](readme_images/text.png)

### Icon View GUI

Here is a closer look of Icon GUI:

* To open a folder you left-click on the icon (only one click is needed).


![icon](readme_images/icon.png)

* To go to the parent directory of the current directory, left-click on the 'back arrow':

![back](readme_images/back.png)

### Search GUI

* You can search for a file path by typing the file name into the search bar:

![search](readme_images/search.png)

* You can run/open the file in the default program by left-clicking on the file path:
  * Note: This feature will be available in some of the future commits.
  
![path](readme_images/searchRun.png)

---

# Updates

### Tree View

### Icon View
- Display of the *current path*.
- *Drag and drop* file manipulation.

### Search View
- *File manipulation* for file path output (run, delete).

### Backend
- **Cross-platform** support.

---

# License

* Check out the LICENSE file.

---

# Sources

* **Icons** used for Icon View window (./textures/icons) are downloaded for free from [**here**](https://www.flaticon.com).
* **Icon-font** used for Tree View window (*./fonts/OpenFontIcons.ttf*) is downloaded from [**this GitHub repo**](https://github.com/traverseda/OpenFontIcons).

---

# Patch Notes 22.2.2025.

- **Dark theme**
  
![darkTheme](readme_images/darkTheme.png)

- **Loading screen**
  
![loading](readme_images/loading.png)

- **Theme choice**

![choice](readme_images/choice.png)

- Implementation for **Delete** option for *Files*.
  
![confirm](readme_images/confirm.png)

![confirm2](readme_images/confirm2.png)

- **Synchronization** of filesystem *cache state* (needed for searching).

---

# Patch Notes 6.3.2025.

- **Running a File in Icon View**
  * By clicking on a File icon, the file will run in the default program for that file type.


- **Current path display**
  
![pathLight](readme_images/pathDark.png)
![pathDark](readme_images/pathLight.png)



