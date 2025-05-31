# ♟️ Chess in SFML

A graphical chessboard built entirely in C++ using SFML 3.0. This project showcases object-oriented design and event-based graphics programming with interactive mouse support for selecting chessboard squares. All pieces are displayed in their correct initial positions.

---

## 💻 Tech Stack

- **Language:** C++17  
- **Graphics Library:** SFML 3.0  
- **Build System:** CMake ≥ 3.16  
- **Compiler:** MinGW-w64 (GCC 14.2.0, UCRT)  
- **Editor:** Visual Studio Code (✅ recommended with IntelliSense)

🪟 **Platform:** Built and tested for **Windows OS**  
🧰 Ensure these paths are configured in CMakeLists.txt:  
- SFML_DIR = C:/SFML-3.0  
- GCC DLLs = C:/winlibs-x86_64-posix-seh-gcc-14.2.0-.../mingw64/bin

---

## 🚀 Current Stage

✅ Board grid drawn with alternating square colors  
✅ All 12 chess pieces placed at standard initial positions  
✅ Mouse input highlights clicked squares  
❌ Piece movement and rules validation not yet implemented

---

## ⚙️ How to Build and Run (Windows)

1. **Clone the repository:**

   
bash
   git clone <repo-url>
   cd cpp-sfml-chess


2. **Build the project:**

   
bash
   mkdir build
   cd build
   cmake ..
   cmake --build .


3. **Run the executable:**

   
bash
   ./Chess.exe


💡 Use Visual Studio Code with the [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension for a smooth workflow.

---

## 📁 Folder Structure

Chess/
├── assets/               # PNG images for chess pieces (already included)
├── header/               # board.h, pieces.h, piece.h
├── src/                  # main.cpp, board.cpp, pieces.cpp
├── build/                # CMake build folder (auto-generated)
├── CMakeLists.txt        # Build configuration
└── README.md             # Project documentation




## 🔄 Pull Requests

Pull requests will be welcome **after move validation logic is implemented**.  
Stay tuned for an update in this section!



## 📄 License & Asset Credits

Chess piece images used in this project are licensed under [CC0 1.0 Public Domain Dedication](https://creativecommons.org/publicdomain/zero/1.0/).  
Attribution is not required, but we gratefully acknowledge the creators of these public domain assets.